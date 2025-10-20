#include "..\..\..\Headers\Revit\Services\BaseService.h"


namespace Services {

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
	if (controlFilters == nullptr || controlFilters->Count == 0) return false;

	for each (KeyValuePair<String^, String^> kvp in controlFilters) {
		Parameter^ p = TryGetParam(doc, e, kvp.Key);
		String^ actual = ReadParamValue(p);
		String^ expected = kvp.Value;

		if (!Object::Equals(actual, expected)) return false;
	}
	return true;
}

Elements::BaseElement^ BaseService::BuildBaseElement(Document^ doc, Element^ e, IEnumerable<String^>^ requiredParams) {
	auto be = gcnew Elements::BaseElement();

	be->Id = e->Id->IntegerValue;
	be->UniqueId = e->UniqueId;
	be->Name = e->Name;

	Category^ cat = e->Category;
	if (cat != nullptr) {
		be->CategoryName = cat->Name;
		be->BuiltInCategory = cat->Id->IntegerValue;
		be->BuiltInCategoryName = cat->Name;
	}

	if (requiredParams != nullptr) {
		for each (String^ pname in requiredParams) {
			Parameter^ p = TryGetParam(doc, e, pname);
			bool filled = IsFilled(p);
			String^ val = nullptr;

			if (p == nullptr) {
				val = "Параметр отсутствует у типа/экземпляра";
			} else if (!filled) {
				val = "Параметр не заполнен";
			} else {
				val = ReadParamValue(p);
				if (String::IsNullOrEmpty(val)) val = "(Пусто)";
			}
			be->AddParameter(pname, val, filled);
		}
	}
	return be;
}

List<Elements::BaseElement^>^ BaseService::CollectAll(
	IDictionary<String^, String^>^ controlFilters,
	IEnumerable<String^>^ requiredParams) {

	auto result = gcnew List<Elements::BaseElement^>();

	FilteredElementCollector^ col = gcnew FilteredElementCollector(doc_);
	IList<Element^>^ elems = col->WhereElementIsNotElementType()->WhereElementIsViewIndependent()->ToElements();

	for each (Element^ e in elems) {
		if (!MatchFilters(doc_, e, controlFilters)) continue;
		result->Add(BuildBaseElement(doc_, e, requiredParams));
	}
	return result;
}

List<Elements::BaseElement^>^ BaseService::CollectByCategory(
		BuiltInCategory bic,
		IDictionary<String^, String^>^ controlFilters,
		IEnumerable<String^>^ requiredParams) {
	
	auto result = gcnew List<Elements::BaseElement^>();

	FilteredElementCollector^ col = gcnew FilteredElementCollector(doc_);
	col->OfCategory(bic);
	IList<Element^>^ elems = col->WhereElementIsNotElementType()->WhereElementIsViewIndependent()->ToElements();

	for each (Element ^ e in elems) {
		if (!MatchFilters(doc_, e, controlFilters)) continue;
		result->Add(BuildBaseElement(doc_, e, requiredParams));
	}
	return result;
}

Dictionary<String^, List<Elements::BaseElement^>^>^ BaseService::CollectGroupedByCategory(
		IDictionary<String^, String^>^ controlFilters,
		IEnumerable<String^>^ requiredParams) {

	auto map = gcnew Dictionary<String^, List<Elements::BaseElement^>^>();

	FilteredElementCollector^ col = gcnew FilteredElementCollector(doc_);
	IList<Element^>^ elems = col->WhereElementIsNotElementType()->WhereElementIsViewIndependent()->ToElements();

	for each (Element ^ e in elems) {
		if (!MatchFilters(doc_, e, controlFilters)) continue;

		String^ cname = (e->Category != nullptr) ? e->Category->Name : "<Без категории>";
		List<Elements::BaseElement^>^ bucket;
		if (!map->TryGetValue(cname, bucket)) {
			bucket = gcnew List<Elements::BaseElement^>();
			map[cname] = bucket;
		}
		bucket->Add(BuildBaseElement(doc_, e, requiredParams));
	}
	return map;
}
	
}// namespace Service
