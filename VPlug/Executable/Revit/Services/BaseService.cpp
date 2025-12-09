#include "..\..\..\Headers\Revit\Services\BaseService.h"


namespace Services {

BaseService::BaseService(Document^ doc) : doc_(doc) {}

Parameter^ BaseService::TryGetParam(Document^ doc, Element^ e, String^ name) {

	if (e == nullptr || String::IsNullOrEmpty(name)) return nullptr;

	Parameter^ p = e->LookupParameter(name);
	if (p != nullptr) return p;

	ElementId^ tid = e->GetTypeId();
	if (tid != nullptr && tid->IntegerValue != -1) {
		Element^ et = doc->GetElement(tid);
		if (et != nullptr) return et->LookupParameter(name);
	}
	return nullptr;
}

String^ BaseService::ReadParamValue(Parameter^ param) {

	if (param == nullptr) return nullptr;

	switch (param->StorageType) {
		case StorageType::Double : return param->AsValueString();
		case StorageType::Integer : return param->AsInteger().ToString();
		case StorageType::String : return param->AsString();
		case StorageType::ElementId : return param->AsElementId()->IntegerValue.ToString();
		default : return nullptr;
	}
}

bool BaseService::IsFilled(Parameter^ param) {

	if (param == nullptr) return false;
	if (!param->HasValue) return false;

	if (param->StorageType == StorageType::String) {
		String^ s = param->AsString();
		return !String::IsNullOrWhiteSpace(s);
	}
	return true;
}

bool BaseService::MatchFilters(Document^ doc, Element^ e, IDictionary<String^, String^>^ controlFilters) {
	//если фильтров нет — считаем, что элемент подходит
	if (controlFilters == nullptr || controlFilters->Count == 0) return true;

	for each (KeyValuePair<String^, String^> kvp in controlFilters) {
		Parameter^ p = TryGetParam(doc, e, kvp.Key);
		String^ actual = ReadParamValue(p);
		String^ expected = kvp.Value;

		if (!Object::Equals(actual, expected)) return false;
	}
	return true;
}

bool BaseService::MatchFilters(Document^ doc, Element^ e, IDictionary<String^, IList<String^>^>^ controlFilters) {
	//если фильтров нет — считаем, что элемент подходит
	if (controlFilters == nullptr || controlFilters->Count == 0) return true;

	for each (KeyValuePair<String^, IList<String^>^> kvp in controlFilters) {
		Parameter^ p = TryGetParam(doc, e, kvp.Key);
		String^ actual = ReadParamValue(p);
		bool pass = false;	
		for each (String^ expected in kvp.Value) {
			if (Object::Equals(actual, expected)) pass = true;
		}
		if (pass == false) return false;
	}
	return true;
}

generic <typename TElement>
TElement BaseService::BuildBaseElement(Document^ doc, Element^ e, IEnumerable<String^>^ requiredParams) {

	auto tElement = gcnew TElement();

	tElement->Id = e->Id->IntegerValue;
	tElement->UniqueId = e->UniqueId;
	tElement->Name = e->Name;

	Category^ category = e->Category;
	if (category != nullptr) {
		tElement->CategoryName = category->Name;	

		BuiltInCategory bic = static_cast<BuiltInCategory>(category->Id->IntegerValue);
		tElement->BuiltInCategory = static_cast<int>(bic);
		tElement->BuiltInCategoryName = bic.ToString();
	}

	if (requiredParams != nullptr) {
		for each (String^ parameterName in requiredParams) {
			Parameter^ parameter = TryGetParam(doc, e, parameterName);
			bool filled = IsFilled(parameter);

			MyDomain::Parameters::ParameterStatus status;
			String^ value = nullptr;

			if (parameter == nullptr) {
				status = MyDomain::Parameters::ParameterStatus::Missing;
			} else if (!filled) {
				status = MyDomain::Parameters::ParameterStatus::Empty;
			} else {
				status = MyDomain::Parameters::ParameterStatus::Filled;
				value = ReadParamValue(parameter);

				if (String::IsNullOrEmpty(value)) status = MyDomain::Parameters::ParameterStatus::Empty;
			}
			
			MyDomain::Parameters::Parameter^ dParameter = gcnew MyDomain::Parameters::Parameter;
			dParameter->Name = parameterName;
			dParameter->Value = value;
			dParameter->Filled = filled;
			dParameter->Status = status;

			tElement->Parameters->Add(dParameter);
		}
	}
	return tElement;
}

generic <typename TElement>
TElement BaseService::BuildBaseElement(Document^ doc, Element^ e) {

	auto tElement = gcnew TElement();

	tElement->Id = e->Id->IntegerValue;
	tElement->UniqueId = e->UniqueId;
	tElement->Name = e->Name;

	Category^ category = e->Category;
	if (category != nullptr) {
		tElement->CategoryName = category->Name;	

		BuiltInCategory bic = static_cast<BuiltInCategory>(category->Id->IntegerValue);
		tElement->BuiltInCategory = static_cast<int>(bic);
		tElement->BuiltInCategoryName = bic.ToString();
	}
	return tElement;
}

List<MyDomain::Elements::Element^>^ BaseService::CollectAll(IDictionary<String^, String^>^ controlFilters,
		IEnumerable<String^>^ requiredParams) {

	auto result = gcnew List<MyDomain::Elements::Element^>();

	FilteredElementCollector^ fec = gcnew FilteredElementCollector(doc_);
	IList<Element^>^ elements = fec->WhereElementIsNotElementType()->WhereElementIsViewIndependent()->ToElements();

	for each (Element^ element in elements) {
		if (!MatchFilters(doc_, element, controlFilters)) continue;
		result->Add(BuildBaseElement<MyDomain::Elements::Element^>(doc_, element, requiredParams));
	}
	return result;
}

List<MyDomain::Elements::Element^>^ BaseService::CollectByCategory(BuiltInCategory bic,
	//IDictionary<String^, String^>^ controlFilters,
	IEnumerable<String^>^ requiredParams) {

	auto result = gcnew List<MyDomain::Elements::Element^>();

	FilteredElementCollector^ fec = gcnew FilteredElementCollector(doc_);
	fec->OfCategory(bic);

	IList<Element^>^ elements = fec->WhereElementIsNotElementType()->WhereElementIsViewIndependent()->ToElements();

	for each (Element^ element in elements) {
		//if (!MatchFilters(doc_, element, controlFilters)) continue;
		result->Add(BuildBaseElement<MyDomain::Elements::Element^>(doc_, element, requiredParams));
	}
	return result;
}

Dictionary<String^, List<MyDomain::Elements::Element^>^>^ BaseService::CollectGroupedByCategory (
	IDictionary<String^, String^>^ controlFilters,
	IEnumerable<String^>^ requiredParams) {

	auto result = gcnew Dictionary<String^, List<MyDomain::Elements::Element^>^>();

	FilteredElementCollector^ fec = gcnew FilteredElementCollector(doc_);
	IList<Element^>^ elements = fec->WhereElementIsNotElementType()->WhereElementIsViewIndependent()->ToElements();

	for each (Element^ element in elements) {
		if (!MatchFilters(doc_, element, controlFilters)) continue;
	
		String^ categoryName = (element->Category != nullptr) ? element->Category->Name : "<Без категории>";

		List<MyDomain::Elements::Element^>^ bucket;

		if (!result->TryGetValue(categoryName, bucket)) {
			bucket = gcnew List<MyDomain::Elements::Element^>();
			result[categoryName] = bucket;
		}
		bucket->Add(BuildBaseElement<MyDomain::Elements::Element^>(doc_, element, requiredParams));
	}
	return result;
}

}// namespace Service
