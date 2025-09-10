#pragma once

#include "..\..\Revit\Elements\BaseElement.h"

using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;

namespace Export {

public ref class AuditParameterHtmlExport {
private:
	String^ path_;

public:
	AuditParameterHtmlExport(String^ path);

	void CompileFile(Dictionary<String^, List<Elements::BaseElement^>^>^ data);

};

}