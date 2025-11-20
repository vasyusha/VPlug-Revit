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

generic <typename TElement>
 TElement BaseService::BuildBaseElement(Document^ doc, Element^ e, IEnumerable<String^>^ requiredParams) {
	auto be = gcnew TElement();

	be->Id = e->Id->IntegerValue;
	be->UniqueId = e->UniqueId;
	be->Name = e->Name;

	Category^ cat = e->Category;
	if (cat != nullptr) {
		be->CategoryName = cat->Name;

		BuiltInCategory bic = static_cast<BuiltInCategory>(cat->Id->IntegerValue);
		be->BuiltInCategory = (int)bic;
		be->BuiltInCategoryName = bic.ToString();
	}

	if (requiredParams != nullptr) {
		for each (String^ pname in requiredParams) {
			Parameter^ p = TryGetParam(doc, e, pname);
			bool filled = IsFilled(p);
			Elements::ParamState stage;
			String^ val = nullptr;

			if (p == nullptr) {
				stage = Elements::ParamState::MissingParam;
			} else if (!filled) {
				stage = Elements::ParamState::EmptyValue;
			} else {
				stage = Elements::ParamState::Ok;
				val = ReadParamValue(p);
				if (String::IsNullOrEmpty(val)) stage = Elements::ParamState::EmptyValue;
			}
			be->AddParameter(pname, val, filled, stage);
		}
	}
	return be;
}

generic <typename TElement>
 TElement BaseService::BuildBaseElement(Document^ doc, Element^ e) {
	auto be = gcnew TElement();

	be->Id = e->Id->IntegerValue;
	be->UniqueId = e->UniqueId;
	be->Name = e->Name;

	Category^ cat = e->Category;
	if (cat != nullptr) {
		be->CategoryName = cat->Name;

		BuiltInCategory bic = static_cast<BuiltInCategory>(cat->Id->IntegerValue);
		be->BuiltInCategory = (int)bic;
		be->BuiltInCategoryName = bic.ToString();
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
		result->Add(BuildBaseElement<Elements::BaseElement^>(doc_, e, requiredParams));
	}
	return result;
}

List<Elements::BaseElement^>^ BaseService::CollectByCategory(
		BuiltInCategory bic,
		//IDictionary<String^, String^>^ controlFilters,
		IEnumerable<String^>^ requiredParams) {
	
	auto result = gcnew List<Elements::BaseElement^>();

	FilteredElementCollector^ col = gcnew FilteredElementCollector(doc_);
	col->OfCategory(bic);
	IList<Element^>^ elems = col->WhereElementIsNotElementType()->WhereElementIsViewIndependent()->ToElements();

	for each (Element ^ e in elems) {
		//if (!MatchFilters(doc_, e, controlFilters)) continue;
		result->Add(BuildBaseElement<Elements::BaseElement^>(doc_, e, requiredParams));
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
		bucket->Add(BuildBaseElement<Elements::BaseElement^>(doc_, e, requiredParams));
	}
	return map;
}
	
}// namespace Service
