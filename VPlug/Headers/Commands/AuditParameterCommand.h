#pragma once
#include <msclr/marshal_cppstd.h>
#include "..\..\Headers\Config\json\JsonReaderAuditParameter.h"
#include "..\UI\VPForms\VPFormAuditParameterCommand.h"
#include "..\..\Headers\Revit\Services\BaseService.h"
#include "..\..\Headers\Export\html\AuditParameter_htmlExport.h"

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
	Dictionary<Tuple<String^, String^>^, List<Elements::BaseElement^>^>^ category_base_element_;

	ref struct CategoryFilter {
		int32_t id;
		String^ name;
		List<String^>^ parameters;
	};

	ref struct ParameterCheckFilter {
		String^ name;
		String^ expected_value;
	};

	ref struct UniversalFilter {
		List<ParameterCheckFilter^>^ parameter_value_filter;
		List<String^>^ parameters;
	};

	Dictionary<int, CategoryFilter^>^ category_;
	Dictionary<int, UniversalFilter^>^ universal_;

public:
	virtual Result Execute(ExternalCommandData^ command_data, 
		String^% message, ElementSet^ elements);

	void SetParseConfigJSON(Object^ sender, EventArgs^ e);
	void SetParseJSON(Object^ sender, EventArgs^ e);
	void Audit(Object^ sender, EventArgs^ e);
	void GetResultAudit(Object^ sender, EventArgs^ e);

	enum class VerificationMethod {
		Category,
		Filter
	};
private:
	VerificationMethod verification_method_;

};

}
