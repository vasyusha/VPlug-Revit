#pragma once

#include "../../Headers/UI/MyForms/FormAuditWallOpening.h"
#include "../../Headers/Revit/Services/WallService.h"
#include "../../Headers/Domain/WallOpeningDomain.h"
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
	/*
	Document^ doc_;
	MyForm::FormAuditWallOpening^ form_;

	void SubscriptionEvent();

	void Audit(IDictionary<String^, String^>^ filters);

	List<String^>^ PrepareFilterValue(String^ value);
	void PrepareElement(Elements::WallElement^ wallElement);
	void PrepareType(Elements::WallElement^ wallElement);

	void FillTable();

	void Export(String^ path);

	MyDomain::WallOpening::WallOpeningReport^ report;
	*/
public:
	virtual Result Execute(ExternalCommandData^ commandData,
		String^% message, ElementSet^ elements);
};

}//namespace Commands










