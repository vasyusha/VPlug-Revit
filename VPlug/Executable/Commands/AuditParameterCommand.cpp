#include "../../Headers/Commands/AuditParameterCommand.h"

namespace Commands {

String^ AuditScopeSummary::Scope::get() {
	return scope_;
}

void AuditScopeSummary::Scope::set(String^ value) {
	scope_ = value;
}

bool AuditScopeSummary::Pass::get() {
	return pass_;
}

void AuditScopeSummary::Pass::set(bool value) {
	pass_ = value;
}

int AuditScopeSummary::TotalElement::get() {
	return totalElement_;
}

void AuditScopeSummary::TotalElement::set(int value) {
	totalElement_ = value;
}

int AuditScopeSummary::PassedElement::get() {
	return passElement_;
}

void AuditScopeSummary::PassedElement::set(int value) {
	passElement_ = value;
}

int AuditScopeSummary::FailedElement::get() {
	return failedElement_;
}

void AuditScopeSummary::FailedElement::set(int value) {
	failedElement_ = value;
}

int AuditScopeSummary::TotalParam::get() {
	return totalParam_;
}

void AuditScopeSummary::TotalParam::set(int value) {
	totalParam_ = value;
}

int AuditScopeSummary::PassedParam::get() {
	return passedParam_;
}

void AuditScopeSummary::PassedParam::set(int value) {
	passedParam_ = value;
}

int AuditScopeSummary::MissedValue::get() {
	return missedValue_;
}

void AuditScopeSummary::MissedValue::set(int value) {
	missedValue_ = value;
}

int AuditScopeSummary::NoParam::get() {
	return noParam_;
}

void AuditScopeSummary::NoParam::set(int value) {
	noParam_ = value;
}

AuditResults::AuditResults() {
	auditScopeSummary = gcnew List<AuditScopeSummary^>();
}

bool AuditResults::Pass::get() {
	return pass_;
}

void AuditResults::Pass::set(bool value) {
	pass_ = value;
}

int AuditResults::SpecPass::get() {
	return specPass_;
}

void AuditResults::SpecPass::set(int value) {
	specPass_ = value;
}

int AuditResults::SpecTotal::get() {
	return specTotal_;
}

void AuditResults::SpecTotal::set(int value) {
	specTotal_ = value;
}

int AuditResults::ReqPass::get() {
	return reqPass_;
}

void AuditResults::ReqPass::set(int value) {
	reqPass_ = value;
}

int AuditResults::ReqTotal::get() {
	return reqTotal_;
}

void AuditResults::ReqTotal::set(int value) {
	reqTotal_ = value;
}

int AuditResults::CheckPass::get() {
	return checkPass_;
}

void AuditResults::CheckPass::set(int value) {
	checkPass_ = value;
}

int AuditResults::CheckTotal::get() {
	return checkTotal_;
}

void AuditResults::CheckTotal::set(int value) {
	checkTotal_ = value;
}

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

	if (method_ == "Категория") {
		AuditCategory();
	} else if (method_ == "Фильтр") {
		AuditUserFilter();
	} else {
		MessageBox::Show("Неизвестный метод проверки");
		form_->MarkAuditFinished(false);
		return;
	}
	form_->MarkAuditFinished(true);
}

void AuditParameterCommand::AuditCategory() {
	elements_ = gcnew Dictionary<String^, List<Elements::BaseElement^>^>();

	dataScopes_ = gcnew Dictionary<String^, AuditScopeSummary^>();
	
	Services::BaseService^ service = gcnew Services::BaseService(doc_);	

	groupCheckParameters_ = gcnew Dictionary<String^, List<String^>^>();

	for each (String^ scope in checksSelected_) {
		if (!categorySpecs_->ContainsKey(scope)) continue;

			List<Elements::BaseElement^>^ es = service->CollectByCategory(
			static_cast<BuiltInCategory>(categorySpecs_[scope]->Id),
			categorySpecs_[scope]->Parameters
		);

		groupCheckParameters_->Add(scope, categorySpecs_[scope]->Parameters);	

		elements_->Add(scope, es);

		dataScopes_->Add(scope, CreateDataScope(scope, es));

		CompileAuditResult(dataScopes_[scope]);
	}
	FillTable();
}

void AuditParameterCommand::AuditUserFilter() {
	elements_ = gcnew Dictionary<String^, List<Elements::BaseElement^>^>();
	
	dataScopes_ = gcnew Dictionary<String^, AuditScopeSummary^>();

	Services::BaseService^ service = gcnew Services::BaseService(doc_);	

	groupCheckParameters_ = gcnew Dictionary<String^, List<String^>^>();

	for each(String^ scope in checksSelected_) {
		if (!userFilterSpecs_->ContainsKey(scope)) continue;

		Dictionary<String^, String^>^ filter = gcnew Dictionary<String^, String^>();
		for each (JsonReader::Filter^ f in userFilterSpecs_[scope]->Filters) {
			filter->Add(f->Name, f->Value);
		}

		List<Elements::BaseElement^>^ es = service->CollectAll(
			filter,
			userFilterSpecs_[scope]->Parameters
		);

		groupCheckParameters_->Add(scope, categorySpecs_[scope]->Parameters);	

		elements_->Add(scope, es);

		dataScopes_->Add(scope, CreateDataScope(scope, es));

		CompileAuditResult(dataScopes_[scope]);
	}
	FillTable();
}

AuditScopeSummary^ AuditParameterCommand::CreateDataScope(String^ scope, IList<Elements::BaseElement^>^ elements) {
	AuditScopeSummary^ dataScope = gcnew AuditScopeSummary();

	dataScope->Scope = scope;
	dataScope->TotalElement = elements->Count;
	bool passScope = true;
	for each (Elements::BaseElement^ e in elements) {
		
		bool elementPassed = true;

		for each (Elements::ParamResult^ p in e->Parameters) {
			++dataScope->TotalParam;
			switch (p->Stage) {
				case Elements::ParamState::MissingParam : ++dataScope->NoParam;
					break;
				case Elements::ParamState::EmptyValue : ++dataScope->MissedValue;
					break;
				case Elements::ParamState::Ok : ++dataScope->PassedParam;
					break;
			}

			if (p->Stage != Elements::ParamState::Ok) elementPassed = false;
		}

		if (elementPassed) {
			++dataScope->PassedElement;
		} else {
			++dataScope->FailedElement;
			passScope = false;
		}
	}
	dataScope->Pass = passScope;
	return dataScope;
}

void AuditParameterCommand::CompileAuditResult(AuditScopeSummary^ scopeSummary) {
	if (res_ == nullptr) {
		res_ = gcnew AuditResults();
	}

	if (res_->Pass == true) {
		res_->Pass = scopeSummary->Pass;
	}

	res_->SpecPass = scopeSummary->Pass == true ? ++res_->SpecPass : res_->SpecPass;
	++res_->SpecTotal;
	res_->ReqPass += scopeSummary->PassedElement;
	res_->ReqTotal += scopeSummary->TotalElement;
	res_->CheckPass += scopeSummary->PassedParam;
	res_->CheckTotal += scopeSummary->TotalParam;

	res_->auditScopeSummary->Add(scopeSummary);

}

void AuditParameterCommand::FillTable() {
	form_->ClearTable();
	for each (KeyValuePair<String^, AuditScopeSummary^> ds in dataScopes_) {
		MyForm::AuditSummaryRow^ row = gcnew MyForm::AuditSummaryRow();

		row->Scope = ds.Value->Scope;
		row->Total = ds.Value->TotalElement;
		row->Passed = ds.Value->PassedElement;
		row->Failed = ds.Value->FailedElement;
		row->MissedValue = ds.Value->MissedValue;
		row->NoParam = ds.Value->NoParam;

		form_->AddRowTable(row);
	}
}

void AuditParameterCommand::Export(String^ path) {
	ExportHtml::CategoryReport^ category;

	ExportHtml::ReportModel^ repModel = gcnew ExportHtml::ReportModel();
	for each (KeyValuePair<String^, AuditScopeSummary^> kvp in dataScopes_) {
		if (!elements_->ContainsKey(kvp.Key)) continue;
		category = gcnew ExportHtml::CategoryReport();
		category->ChecksPass = kvp.Value->PassedParam;
		category->ChecksTotal = kvp.Value->TotalParam;
		category->ElementsTotal = kvp.Value->TotalElement;
		category->ElementsPass = kvp.Value->PassedElement;
		category->Percent = System::Math::Floor(((double)kvp.Value->PassedElement / kvp.Value->TotalElement) * 100);
		category->Slug = kvp.Value->Scope;
		category->Name = kvp.Key;
		category->Pass = kvp.Value->Pass;
		category->CheckedParameters = groupCheckParameters_[kvp.Key];

		for each (Elements::BaseElement^ e in elements_[kvp.Key]) {
			ExportHtml::RequirementRow^ row = gcnew ExportHtml::RequirementRow();
			row->Id = e->Id;
			row->Name = e->Name;
			
			bool pass = true;

			for each (Elements::ParamResult^ p in e->Parameters) {
				if (p->Filled == false) pass = false;
				
				ExportHtml::RequirementRow::Param^ ep = gcnew ExportHtml::RequirementRow::Param();
		
				ep->Name = p->Name;
				ep->Value = p->Value;
				ep->Filled = p->Filled;

				row->Params->Add(ep);
			}

			row->Pass = pass;
			category->Requirements->Add(row);
		}
		if (category != nullptr) repModel->Categories->Add(category);

	}

	repModel->SpecPass = res_->SpecPass;
	repModel->SpecTotal = res_->SpecTotal;
	repModel->ReqPass = res_->ReqPass;
	repModel->ReqTotal = res_->ReqTotal;
	repModel->CheckPass = res_->CheckPass;
	repModel->CheckTotal = res_->CheckTotal;
	repModel->Percent = (int)System::Math::Floor(((double)res_->SpecPass / res_->SpecTotal) * 100);
	
	repModel->FilePath = "file path";
	repModel->ProjectName = "project name";
	repModel->DataTimeStr = "data time";

	ExportHtml::AuditParameterExportHtml^ exp = gcnew ExportHtml::AuditParameterExportHtml();
	exp->SaveHtmlToFile(repModel, path);
}

}// namespace Commands

