#pragma once
#include "..\Elements\BaseElement.h"
#include "..\Filters\ElementCollectorFilter.h"
#include "..\Filters\ParameterFilledFilter.h"

using namespace Autodesk::Revit::UI;
using namespace Autodesk::Revit::DB;
using namespace Autodesk::Revit::Attributes;

using namespace System;
using namespace System::Collections::Generic;

namespace Services {

public ref class BaseService {
private:
	Document^ doc_;
	List<Elements::BaseElement^>^ elements_;

public:
	BaseService(Document^ doc, int category_id, List<String^>^ parameters);

	void SetElements(List<Element^>^ elements, List<String^>^ parameters);
	List<Elements::BaseElement^>^ GetElemenst();	
};

}