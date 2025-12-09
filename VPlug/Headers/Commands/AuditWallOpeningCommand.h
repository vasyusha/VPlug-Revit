#pragma once

#include "../../Headers/UI/MyForms/FormAuditWallOpening.h"
#include "../../Headers/Revit/Services/WallService.h"
#include "../../Headers/Domain/ReportDomain.h"
#include "../../Headers/Export/html/AuditWallOpeningExportHtml.h"

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;

using namespace Autodesk::Revit::UI;
using namespace Autodesk::Revit::DB;
using namespace Autodesk::Revit::Attributes;

namespace Commands {

[Transaction(TransactionMode::Manual)]
public ref class AuditWallOpeningCommand : public IExternalCommand {
private:
	Document^ doc_;
	MyForm::FormAuditWallOpening^ form_;

	void SubscriptionEvent();

	void Audit(IDictionary<String^, String^>^ filters);

	List<String^>^ PrepareFilterValue(String^ value);

	String^ BuildScopKey(List<MyDomain::Elements::AuditWallOpenings::Scop^>^ scops);

	void AuditElement(List<MyDomain::Elements::WallElement^>^ wallElements);
	void CollectAuditGroup(String^ key, MyDomain::Elements::AuditWallOpenings::AuditWallElement^ auditElement);
	
	void FillTable();

	void Export(String^ path);

	//Парам - значения
	Dictionary<String^, IList<String^>^>^ filters_;

	Dictionary<String^, List<MyDomain::Elements::AuditWallOpenings::AuditWallElement^>^>^ scopAuditWallElements_;
	Dictionary<String^, MyDomain::Elements::AuditWallOpenings::AuditWallGroup^>^ scopAuditWallGroups_;

	MyDomain::Elements::AuditWallOpenings::AuditResult^ auditResult_;

	MyDomain::AuditWallOpeningsReport::ResultReport^ reportResult_;

public:
	virtual Result Execute(ExternalCommandData^ commandData,
		String^% message, ElementSet^ elements);
};

}//namespace Commands










