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

	for each (String^ scope in checksSelected_) {
		if (!categorySpecs_->ContainsKey(scope)) continue;

			List<Elements::BaseElement^>^ es = service->CollectByCategory(
			static_cast<BuiltInCategory>(categorySpecs_[scope]->Id),
			categorySpecs_[scope]->Parameters
		);

		elements_->Add(scope, es);

		dataScopes_->Add(scope, CreateDataScope(scope, es));
	}
	FillTable();
}

void AuditParameterCommand::AuditUserFilter() {
	elements_ = gcnew Dictionary<String^, List<Elements::BaseElement^>^>();
	
	dataScopes_ = gcnew Dictionary<String^, AuditScopeSummary^>();

	Services::BaseService^ service = gcnew Services::BaseService(doc_);	

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

		elements_->Add(scope, es);

		dataScopes_->Add(scope, CreateDataScope(scope, es));
	}
	FillTable();
}

AuditScopeSummary^ AuditParameterCommand::CreateDataScope(String^ scope, IList<Elements::BaseElement^>^ elements) {
	AuditScopeSummary^ dataScope = gcnew AuditScopeSummary();

	dataScope->Scope = scope;
	dataScope->Total = elements->Count;

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
			++dataScope->Passed;
		} else {
			++dataScope->Failed;
		}
	}
	return dataScope;
}

void AuditParameterCommand::FillTable() {
	form_->ClearTable();
	for each (KeyValuePair<String^, AuditScopeSummary^> ds in dataScopes_) {
		MyForm::AuditSummaryRow^ row = gcnew MyForm::AuditSummaryRow();

		row->Scope = ds.Value->Scope;
		row->Total = ds.Value->Total;
		row->Passed = ds.Value->Passed;
		row->Failed = ds.Value->Failed;
		row->MissedValue = ds.Value->MissedValue;
		row->NoParam = ds.Value->NoParam;

		form_->AddRowTable(row);
	}
}

void AuditParameterCommand::Export(String^ path) {
	ExportHtml::CategoryReport^ category = gcnew ExportHtml::CategoryReport();

	for each (KeyValuePair<String^, AuditScopeSummary^> kvp in dataScopes_) {
		if (!elements_->ContainsKey(kvp.Key)) continue;

		category->ChecksPass = kvp.Value->PassedParam;
		category->ChecksTotal = kvp.Value->TotalParam;
		category->ElementsTotal = kvp.Value->Total;
		category->ElementsPass = kvp.Value->Passed;
		category->Percent = (kvp.Value->TotalParam * kvp.Value->PassedParam) / 100;
		category->Slug = kvp.Value->Scope;

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

	}
}

}// namespace Commands

