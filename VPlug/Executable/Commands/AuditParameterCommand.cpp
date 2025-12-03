#include "../../Headers/Commands/AuditParameterCommand.h"

namespace Commands {

Result AuditParameterCommand::Execute(ExternalCommandData^ commandData,
	String^% message, ElementSet^ elements) {

	UIDocument^ uiDoc = commandData->Application->ActiveUIDocument;
	doc_ = uiDoc->Document;
		
	form_ = gcnew MyForm::FormAuditParameter();

	SubscriptionEvent();
	SetAvailableMethods();
	
	form_->ShowDialog();

	return Result::Succeeded;
}

void AuditParameterCommand::SubscriptionEvent() {
	form_->MethodChanged += gcnew MyForm::AuditMethodSelectedHandler(this, &AuditParameterCommand::GetMethod);
	form_->LoadConfigRequest += gcnew MyForm::AuditConfigLoadedHandler(this, &AuditParameterCommand::GetConfigPath);
	form_->ChecksSelectedRequest += gcnew MyForm::AuditChecksSelectedHandler(this, &AuditParameterCommand::GetOnChecks);
	form_->RunRequest += gcnew MyForm::AuditRunningHandler(this, &AuditParameterCommand::Audit);		
	form_->ExportRequest += gcnew MyForm::AuditExportHandler(this, &AuditParameterCommand::Export);
}

void AuditParameterCommand::SetAvailableMethods() {
	List<String^>^ methods = gcnew List<String^>();
	methods->Add("Категория");
	methods->Add("Фильтр");

	form_->SetAvailableMethods(methods);
}

void AuditParameterCommand::GetMethod(String^ method) {
	if (method != nullptr ) {
		method_ = method;
	}
	form_->MarkAuditMethodPrepared(method != nullptr);
}

void AuditParameterCommand::GetConfigPath(String^ path) {
	form_->MarkAuditConfigPrepared(path != nullptr);

	if (path != nullptr) {
		configPath_ = path;
		StartPrepare();
	}
}

void AuditParameterCommand::StartPrepare() {
	checks_ = gcnew List<String^>();

	if (method_ == "Категория") {
		PrepareCategory();
	} else if (method_ == "Фильтр") {
		PrepareUserFilterSpec();
	} else {
		MessageBox::Show("Ошибка подготовки", "Ошибка");
		return;
	}
	form_->SetChecks(checks_);
}

void AuditParameterCommand::PrepareCategory() {
	List<JsonReader::CategorySpec^>^ specs = JsonReader::JsonReaderAuditParameter::LoadCategorySpecs(configPath_);
	
	if (specs == nullptr || specs->Count <= 0) return;

	categorySpecs_ = gcnew Dictionary<String^, JsonReader::CategorySpec^>();

	for each (JsonReader::CategorySpec^ spec in specs) {
		checks_->Add(spec->Name);
		categorySpecs_->Add(spec->Name, spec);
	}
}

void AuditParameterCommand::PrepareUserFilterSpec() {
	List<JsonReader::UserFilterSpec^>^ specs = JsonReader::JsonReaderAuditParameter::LoadUserFilterSpec(configPath_);

	if (specs == nullptr || specs->Count <= 0) return;

	userFilterSpecs_ = gcnew Dictionary<String^, JsonReader::UserFilterSpec^>();

	for each (JsonReader::UserFilterSpec^ spec in specs) {
		checks_->Add(spec->Name);
		userFilterSpecs_->Add(spec->Name, spec);
	}
}

void AuditParameterCommand::GetOnChecks(List<String^>^ selected) {
	checksSelected_ = selected;
}

void AuditParameterCommand::Audit() {
	if (checksSelected_ == nullptr || checksSelected_->Count == 0) {
		MessageBox::Show("Не выбрано ни одной группы для проверки");
		form_->MarkAuditFinished(false);
		return;
	}
	
	scopCheckParameters_ = gcnew Dictionary<String^, List<String^>^>();
	scopAuditElements_ = gcnew Dictionary<String^, List<MyDomain::Elements::AuditParameters::AuditElement^>^>();
	scopAuditGroups_ = gcnew Dictionary<String^, MyDomain::Elements::AuditParameters::AuditGroup^>();
	auditResult_ = gcnew MyDomain::Elements::AuditParameters::AuditResult();
	
	if (method_ == "Категория") {
		AuditByCategory();
	} else if (method_ == "Фильтр") {
		AuditByUserFilter();
	} else {
		MessageBox::Show("Неизвестный метод проверки");
		form_->MarkAuditFinished(false);
		return;
	}
	CreateReport();
	form_->MarkAuditFinished(true);
}

void AuditParameterCommand::AuditElements(
	List<MyDomain::Elements::Element^>^ elements,
		String^ scop) {

	List<MyDomain::Elements::AuditParameters::AuditElement^>^ result = gcnew List<MyDomain::Elements::AuditParameters::AuditElement^>();

	MyDomain::Elements::AuditParameters::AuditGroup^ auditGroup = gcnew MyDomain::Elements::AuditParameters::AuditGroup();

	auditGroup->Pass = true;
	auditGroup->Name = scop;
	auditGroup->TotalElements = elements->Count;
	auditGroup->CheckedParameters = scopCheckParameters_[scop];

	for each (MyDomain::Elements::Element^ element in elements) {

		MyDomain::Elements::AuditParameters::AuditElement^ auditElement = gcnew MyDomain::Elements::AuditParameters::AuditElement();

		auditElement->Element = element;
		auditElement->Pass = true;
		auditElement->TotalParams = element->Parameters->Count;

		for each (MyDomain::Parameters::Parameter^ parameter in element->Parameters) {
			switch (parameter->Status) {
				case MyDomain::Parameters::ParameterStatus::Filled : {
					++auditElement->FilledParams;
					++auditElement->PassParams;
					break;
				}
				case MyDomain::Parameters::ParameterStatus::Empty : {
					++auditElement->EmptyParams;
					++auditElement->FailParams;
					break;
				}
				case MyDomain::Parameters::ParameterStatus::Missing : {
					++auditElement->MissingParams;
					++auditElement->FailParams;
					break;
				}
			}
			if (parameter->Status != MyDomain::Parameters::ParameterStatus::Filled && auditElement->Pass == true) {
				auditElement->Pass = false;
			}
		}

		if (auditElement->PassParams > 0 && auditElement->TotalParams > 0) {
			auditElement->Percent = System::Math::Floor((static_cast<double>(auditElement->PassParams) / auditElement->TotalParams) * 100);
		} else {
			auditElement->Percent = 0;
		}
		CollectAuditGroup(auditElement, auditGroup);
	}
	scopAuditElements_->Add(scop, result);

	if (auditGroup->PassElements > 0 && auditGroup->TotalElements > 0) {
		auditGroup->Percent = System::Math::Floor((static_cast<double>(auditGroup->PassElements) / auditGroup->TotalElements) * 100);
	} else {
		auditGroup->Percent = 0;
	}

	scopAuditGroups_->Add(scop, auditGroup);
	CollectAuditResult(auditGroup);
}

void AuditParameterCommand::CollectAuditGroup(MyDomain::Elements::AuditParameters::AuditElement^ element,

	MyDomain::Elements::AuditParameters::AuditGroup^ group) {
	
	if (group->Pass && element->Pass == false) {
		group->Pass = false;
	}

	if (element->Pass) {
		++group->PassElements;
	} else {
		++group->FailElements;
	}

	group->TotalParams += element->TotalParams;
	group->PassParams += element->PassParams;
	group->FailParams += element->FailParams;
	group->EmptyParams += element->EmptyParams;
	group->MissingParams += element->MissingParams;
	group->Elements->Add(element);
}

void AuditParameterCommand::CollectAuditResult(MyDomain::Elements::AuditParameters::AuditGroup^ group) {

	if (auditResult_->Pass && !group->Pass) {
		auditResult_->Pass = false;
	}

	if (group->Pass) {
		++auditResult_->PassGroups;
	} else {
		++auditResult_->FailGroup;
	}

	++auditResult_->TotalGroups;
	auditResult_->ReqElementPass += group->PassElements;
	auditResult_->ReqElementTotal += group->TotalElements;
	auditResult_->ReqParamPass += group->PassParams;
	auditResult_->ReqParamTotal += group->TotalParams;
	auditResult_->Groups->Add(group);
}


void AuditParameterCommand::AuditByCategory() {

	Services::BaseService^ baseService = gcnew Services::BaseService(doc_);

	for each (String^ scop in checksSelected_) {
		if (!categorySpecs_->ContainsKey(scop)) continue;

		List<MyDomain::Elements::Element^>^ elements = baseService->CollectByCategory(
			static_cast<BuiltInCategory>(categorySpecs_[scop]->Id),
			categorySpecs_[scop]->Parameters
		);

		scopCheckParameters_->Add(scop, categorySpecs_[scop]->Parameters);
		AuditElements(elements, scop);
	}
	
	if (auditResult_->PassGroups > 0 && auditResult_->TotalGroups > 0) {
		auditResult_->Percent = System::Math::Floor((static_cast<double>(auditResult_->PassGroups) / auditResult_->TotalGroups) * 100);
	} else {
		auditResult_->Percent = 0;
	}
	FillTable();
}

void AuditParameterCommand::AuditByUserFilter() {

	Services::BaseService^ baseService = gcnew Services::BaseService(doc_);

	for each (String^ scop in checksSelected_) {
		if (!userFilterSpecs_->ContainsKey(scop)) continue;

		Dictionary<String^, String^>^ filter = gcnew Dictionary<String^, String^>();

		for each (JsonReader::Filter^ readerFilter in userFilterSpecs_[scop]->Filters) {
			filter->Add(readerFilter->Name, readerFilter->Value);
		}

		List<MyDomain::Elements::Element^>^ elements = baseService->CollectAll(
			filter,
			userFilterSpecs_[scop]->Parameters
		);

		scopCheckParameters_->Add(scop, categorySpecs_[scop]->Parameters);
		AuditElements(elements, scop);
	}
	auditResult_->Percent = System::Math::Floor((static_cast<double>(auditResult_->PassGroups) / auditResult_->TotalGroups) * 100);

	FillTable();
}

void AuditParameterCommand::FillTable() {
	form_->ClearTable();
	for each (KeyValuePair<String^, MyDomain::Elements::AuditParameters::AuditGroup^> scopGroup in scopAuditGroups_) {
		MyForm::AuditSummaryRow^ row = gcnew MyForm::AuditSummaryRow();

		row->Scope = scopGroup.Value->Name;
		row->Total = scopGroup.Value->TotalElements;
		row->Passed = scopGroup.Value->PassElements;
		row->Failed = scopGroup.Value->FailElements;
		row->MissedValue = scopGroup.Value->EmptyParams;
		row->NoParam = scopGroup.Value->MissingParams;

		form_->AddRowTable(row);
	}
}

void AuditParameterCommand::CreateReport() {
	resultReport_ = gcnew MyDomain::AuditParameterReport::ResultReport();
	resultReport_->FilePath = doc_->PathName;
	resultReport_->ProjectName = doc_->Title;
	resultReport_->DateTimeStr = System::DateTime::Now.ToString("yyyy-MM-dd HH:mm:ss", System::Globalization::CultureInfo::InvariantCulture);
	resultReport_->Result = auditResult_;
}

void AuditParameterCommand::Export(String^ path) {
	
	ExportHtml::AuditParameterExportHtml^ exp = gcnew ExportHtml::AuditParameterExportHtml();
	exp->SaveHtmlToFile(resultReport_, path);
	
	form_->MarkAuditExportFinished(true);
}
}// namespace Commands

