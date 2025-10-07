#pragma once

using namespace Autodesk::Revit::UI;
using namespace Autodesk::Revit::DB;
using namespace Autodesk::Revit::Attributes;

using namespace System;
using namespace System::Collections::Generic;

namespace Filters {

public ref class ElementCollectorFilter {
private:
	Document^ doc_;
	BuiltInCategory category_;
	Type^ class_type_;
	ElementId^ category_id_;

public:
	ElementCollectorFilter(Document^ doc, BuiltInCategory category);
	ElementCollectorFilter(Document^ doc, Type^ class_type);
	ElementCollectorFilter(Document^ doc, int category_id);

	List<Element^>^ FindElements();

};

}