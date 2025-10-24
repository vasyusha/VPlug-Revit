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
}

void AuditParameterCommand::SetAvailableMethods() {
	List<String^>^ methods = gcnew List<String^>();
	methods->Add("Категория");
	methods->Add("Фильтер");

	form_->SetAvailableMethods(methods);
}

void AuditParameterCommand::GetMethod(String^ method) {
	method_ = method;
}

void AuditParameterCommand::GetConfigPath(String^ path) {
	configPath_ = path;
	StartPrepare();
}

void AuditParameterCommand::StartPrepare() {
	checks_ = gcnew Dictionary<String^, String^>();

	if (method_ == "Категория") {
		PrepareCategory();
	} else {
		PrepareUserFilterSpec();
	}
	form_->SetChecks(checks_);
}

void AuditParameterCommand::PrepareCategory() {
	List<JsonReader::CategorySpec^>^ specs = JsonReader::JsonReaderAuditParameter::LoadCategorySpecs(configPath_);
	
	if (specs == nullptr || specs->Count <= 0) return;

	categorySpecs_ = gcnew Dictionary<String^, JsonReader::CategorySpec^>();

	for each (JsonReader::CategorySpec^ spec in specs) {
		checks_->Add(spec->Name, spec->Name);
		categorySpecs_->Add(spec->Name, spec);
	}
}

void AuditParameterCommand::PrepareUserFilterSpec() {
	List<JsonReader::UserFilterSpec^>^ specs = JsonReader::JsonReaderAuditParameter::LoadUserFilterSpec(configPath_);

	if (specs == nullptr || specs->Count <= 0) return;

	userFilterSpecs_ = gcnew Dictionary<String^, JsonReader::UserFilterSpec^>();

	for each (JsonReader::UserFilterSpec^ spec in specs) {
		checks_->Add(spec->Name, spec->Name);
		userFilterSpecs_->Add(spec->Name, spec);
	}
}

void AuditParameterCommand::GetOnChecks(List<String^>^ selected) {
	checksSelected_ = selected;
}

void AuditParameterCommand::Audit() {
	if (method_ == "Категория") {
		AuditCategory();
	} else {
		AuditUserFilter();
	}
}

void AuditParameterCommand::AuditCategory() {
	elements_ = gcnew Dictionary<String^, List<Elements::BaseElement^>^>();

	dataScops_ = gcnew Dictionary<String^, DataScope^>();
	
	Services::BaseService^ service = gcnew Services::BaseService(doc_);	

	for each (String^ scope in checksSelected_) {
		if (!categorySpecs_->ContainsKey(scope)) continue;

			List<Elements::BaseElement^>^ es = service->CollectByCategory(
			static_cast<BuiltInCategory>(categorySpecs_[scope]->Id),
			categorySpecs_[scope]->Parameters
		);

		elements_->Add(scope, es);

		dataScops_->Add(scope, CreateDataScope(scope, es));
	}
	FillTable();
}

void AuditParameterCommand::AuditUserFilter() {
	elements_ = gcnew Dictionary<String^, List<Elements::BaseElement^>^>();
	
	dataScops_ = gcnew Dictionary<String^, DataScope^>();

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

		dataScops_->Add(scope, CreateDataScope(scope, es));
	}
	FillTable();
}

DataScope^ AuditParameterCommand::CreateDataScope(String^ scope, IList<Elements::BaseElement^>^ elements) {
	DataScope^ dataScope = gcnew DataScope();

	dataScope->Scope = scope;
	dataScope->Total = elements->Count;

	for each (Elements::BaseElement^ e in elements) {
		
		bool elementPassed = true;

		for each (Elements::ParamResult^ p in e->Parameters) {
			if (!p->Filled) {
				elementPassed = false;
				if (p->Value == "Параметр отсутствует у типа/экземпляра") {
					++dataScope->NoParam;
				} else if (p->Value == "Параметр не заполнен" || p->Value == "(Пусто)") {
					++dataScope->MissedValue;
				}
			}
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
	for each (KeyValuePair<String^, DataScope^> ds in dataScops_) {
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



}

