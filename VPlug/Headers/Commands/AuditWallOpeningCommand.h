#pragma once

#include "../../Headers/UI/MyForms/FormAuditWallOpening.h"
#include "../../Headers/Revit/Services/WallService.h"

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

	void Audit(List<Tuple<int, String^, String^>^>^ numFilterValue);

public:
	virtual Result Execute(ExternalCommandData^ commandData,
		String^% message, ElementSet^ elements);
};

}//namespace Commands










