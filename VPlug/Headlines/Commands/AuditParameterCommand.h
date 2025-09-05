#pragma once
#include <msclr/marshal_cppstd.h>
#include "..\..\Headlines\Config\json\json_reader_base.h"
#include "..\UI\VPForms\VPFormAuditParameterCommand.h"

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
	VPForms::VPFormAuditParameterCommand^ form_;

public:
	virtual Result Execute(ExternalCommandData^ command_data, 
		String^% message, ElementSet^ elements);
	
	void SetParseConfigJSON(Object^ sender, EventArgs^ e);
	void SetParseJSON(Object^ sender, EventArgs^ e);
	void GetResultAudit(Object^ sender, EventArgs^ e);

	enum class VerificationMethod {
		Category,
		IfcExportAs	
	};
private:
	VerificationMethod verification_method_;

};

}
