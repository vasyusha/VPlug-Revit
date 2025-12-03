#pragma once

#include "../../Domain/ElementDomain.h"

using namespace Autodesk::Revit::UI;
using namespace Autodesk::Revit::DB;
using namespace Autodesk::Revit::Attributes;

using namespace System;
using namespace System::Collections::Generic;

namespace Services {

public ref class BaseService {
protected:
	Document^ doc_;

	static Parameter^ TryGetParam(Document^ doc, Element^ e, String^ name);

	static String^ ReadParamValue(Parameter^ param);

	static bool IsFilled(Parameter^ param);
	//Жесткое
	static bool MatchFilters(Document^ doc, Element^ e, IDictionary<String^, String^>^ controlFilters);
	//Мягкое
	static bool MatchFilters(Document^ doc, Element^ e, IDictionary<String^, IList<String^>^>^ controlFilters);

	generic <typename TElement>
	where TElement : MyDomain::Elements::Element, gcnew()
	static TElement BuildBaseElement(Document^ doc, Element^ e, IEnumerable<String^>^ requiredParams);

	generic <typename TElement>
	where TElement : MyDomain::Elements::Element, gcnew()
	static TElement BuildBaseElement(Document^ doc, Element^ e);

public:

	BaseService(Document^ doc);

	List<MyDomain::Elements::Element^>^ CollectAll(
		IDictionary<String^, String^>^ controlFilters,
		IEnumerable<String^>^ requiredParams);

	List<MyDomain::Elements::Element^>^ CollectByCategory(
		BuiltInCategory bic,
		//IDictionary<String^, String^>^ controlFilters,
		IEnumerable<String^>^ requiredParams);

	Dictionary<String^, List<MyDomain::Elements::Element^>^>^ CollectGroupedByCategory(
		IDictionary<String^, String^>^ controlFilters,
		IEnumerable<String^>^ requiredParams);


};

}// namespace Service