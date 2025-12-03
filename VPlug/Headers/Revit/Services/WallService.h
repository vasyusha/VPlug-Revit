#pragma once

#include "BaseService.h"
#include "../../Domain/ElementDomain.h"


using namespace System;
using namespace System::Collections::Generic;

using namespace Autodesk::Revit::UI;
using namespace Autodesk::Revit::DB;
using namespace Autodesk::Revit::Attributes;

namespace Services {

public ref class WallService : BaseService {
private:
	//Document^ doc_;	

public:
	WallService(Document^ doc);

	MyDomain::Elements::WallElement^ BuildWallElement(Document^ doc, Element^ e, IEnumerable<String^>^ requiredParams);

	List<MyDomain::Elements::WallElement^>^ CollectByCategory(
		BuiltInCategory bic,
		IDictionary<String^, IList<String^>^>^ controlFilters,
		IEnumerable<String^>^ requiredParams);

	int CountRealOpeningsForWall(Document^ doc, Wall^ wall, MyDomain::Elements::WallElement^ wallElement);


};


}//namespace Service