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

	static Parameter^ TryGetParam(Document^ doc, Element^ e, String^ name);

	static String^ ReadParamValue(Parameter^ param);

	static bool IsFilled(Parameter^ param);

	static bool MatchFilters(Document^ doc, Element^ e, IDictionary<String^, String^>^ controlFilters);

	static Elements::BaseElement^ BuildBaseElement(Document^ doc, Element^ e, IEnumerable<String^>^ requiredParams);

public:

	BaseService(Document^ doc);

	List<Elements::BaseElement^>^ CollectAll(
		IDictionary<String^, String^>^ controlFilters,
		IEnumerable<String^>^ requiredParams);

	List<Elements::BaseElement^>^ CollectByCategory(
		BuiltInCategory bic,
		//IDictionary<String^, String^>^ controlFilters,
		IEnumerable<String^>^ requiredParams);

	Dictionary<String^, List<Elements::BaseElement^>^>^ CollectGroupedByCategory(
		IDictionary<String^, String^>^ controlFilters,
		IEnumerable<String^>^ requiredParams);


};

}// namespace Service