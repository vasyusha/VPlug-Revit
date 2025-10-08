#pragma once

using namespace Autodesk::Revit::UI;
using namespace Autodesk::Revit::DB;
using namespace Autodesk::Revit::Attributes;

using namespace System;
using namespace System::Collections::Generic;

namespace Filters {

public ref class ParameterFilledFilter {
public:
	static String^ CheckParam(Document^ doc, Element^ element, String^ parameter, bool onlyMissing);
};

}