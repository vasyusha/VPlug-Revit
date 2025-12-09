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
	void AuditByCategory();
	void AuditByUserFilter();

	void AuditElements(List<MyDomain::Elements::Element^>^ elements, String^ scop);
	void CollectAuditGroup(MyDomain::Elements::AuditParameters::AuditElement^ element,
		MyDomain::Elements::AuditParameters::AuditGroup^ group
	);
	void CollectAuditResult(MyDomain::Elements::AuditParameters::AuditGroup^ group);

	void FillTable();
	void CreateReport();

	void Export(String^ path);
	
	List<String^>^ checks_;
	List<String^>^ checksSelected_;

	Dictionary<String^, JsonReader::CategorySpec^>^ categorySpecs_;
	Dictionary<String^, JsonReader::UserFilterSpec^>^ userFilterSpecs_;

	Dictionary<String^, List<String^>^>^ scopCheckParameters_;

	Dictionary<String^, List<MyDomain::Elements::AuditParameters::AuditElement^>^>^ scopAuditElements_;
	Dictionary<String^, MyDomain::Elements::AuditParameters::AuditGroup^>^ scopAuditGroups_;
	MyDomain::Elements::AuditParameters::AuditResult^ auditResult_;

	MyDomain::AuditParameterReport::ResultReport^ resultReport_;

public:
	virtual Result Execute(ExternalCommandData^ commandData,
		String^% message, ElementSet^ elements);
};

}// namespace Command
