#pragma once

#include "../../Headers/UI/MyForms/FormAuditParameter.h"
#include "../../Headers/Config/json/JsonReaderAuditParameter.h"
#include "../../Headers/Revit/Services/BaseService.h"
#include "../../Headers/Export/html/AuditParameterExportHtml.h"

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;

using namespace Autodesk::Revit::UI;
using namespace Autodesk::Revit::DB;
using namespace Autodesk::Revit::Attributes;

namespace Commands {

public ref class AuditScopeSummary {
public:
	property String^ Scope;
	property int Total;
	property int Passed;
	property int Failed;
	property int TotalParam;
	property int PassedParam;
	property int MissedValue;
	property int NoParam;
};

[Transaction(TransactionMode::Manual)]
public ref class AuditParameterCommand : public IExternalCommand {
private:
	Document^ doc_;
	MyForm::FormAuditParameter^ form_;

	String^ method_;
	String^ configPath_;
	String^ exportPath_;

	void SubscriptionEvent();

	void SetAvailableMethods();
	void GetMethod(String^ method);
	
	void GetConfigPath(String^ path);

	void StartPrepare();
	void PrepareCategory();
	void PrepareUserFilterSpec();

	void GetOnChecks(List<String^>^ selected);

	void Audit();
	void AuditCategory();
	void AuditUserFilter();

	AuditScopeSummary^ CreateDataScope(String^ scope, IList<Elements::BaseElement^>^ elements);

	void FillTable();

	void Export(String^ path);	

	List<String^>^ checks_;
	List<String^>^ checksSelected_;

	Dictionary<String^, JsonReader::CategorySpec^>^ categorySpecs_;
	Dictionary<String^, JsonReader::UserFilterSpec^>^ userFilterSpecs_;

	Dictionary<String^, List<Elements::BaseElement^>^>^ elements_;

	Dictionary<String^, AuditScopeSummary^>^ dataScopes_;

public:
	virtual Result Execute(ExternalCommandData^ commandData,
		String^% message, ElementSet^ elements);
};

}// namespace Command
