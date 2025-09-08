#pragma once
#include "..\Filters\ElementCollectorFilter.h"

using namespace Autodesk::Revit::UI;
using namespace Autodesk::Revit::DB;
using namespace Autodesk::Revit::Attributes;

using namespace System;
using namespace System::Collections::Generic;

namespace Services {

public ref class BaseService {
private:
	Document^ doc_;

public:
	BaseService(Document^ doc, int category_id, List<String^>^ parameters);
	
};

}