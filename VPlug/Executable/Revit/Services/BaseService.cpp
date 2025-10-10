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

}


/*
Services::BaseService::BaseService(Document^ doc, int category_id, List<String^>^ parameters) 
	: doc_(doc) {
	
	Filters::ElementCollectorFilter^ collector = gcnew Filters::ElementCollectorFilter(doc, category_id);
	List<Element^>^ elements = collector->FindElements();
	
	SetElements(elements, parameters);
}

Services::BaseService::BaseService(Document^ doc, Dictionary<String^, String^>^ controlParValue, List<String^>^ parameters) 
	: doc_(doc) {

	FilteredElementCollector^ collector = gcnew FilteredElementCollector(doc);
	IList<Element^>^ model_element = collector->WhereElementIsNotElementType()->WhereElementIsViewIndependent()->ToElements();
	List<Element^>^ list = gcnew List<Element^>(model_element);

	SetElements(list, controlParValue, parameters);
}


void Services::BaseService::SetElements(List<Element^>^ elements, List<String^>^ parameters) {
	elements_ = gcnew List<Elements::BaseElement^>();

	for each(Element^ e in elements) {
		Elements::BaseElement^ element = gcnew Elements::BaseElement();

		element->SetId(e->Id->IntegerValue);
		element->SetName(e->Name);
		element->SetCategoryName(e->Category->Name);
		element->SetBuiltInCategory(static_cast<BuiltInCategory>(e->Category->Id->IntegerValue).ToString());

		for each(String^ p in parameters) {
			String^ filterValue= Filters::ParameterFilledFilter::CheckParam(doc_, e, p, true);

			Elements::Parameter^ param = gcnew Elements::Parameter();
			param->_name = p;
			param->_value = filterValue;
			if(filterValue == nullptr) param->_filled = false;
			element->SetParameters(param);
		}
		elements_->Add(element);
	}
}

void Services::BaseService::SetElements(List<Element^>^ elements, Dictionary<String^, String^>^ controlParValue, List<String^>^ parameters) {
	elements_ = gcnew List<Elements::BaseElement^>();

	for each (Element^ e in elements) {
		bool flagControl = true;

		for each (KeyValuePair<String^, String^> kvp in controlParValue) {
			String^ filterValue = Filters::ParameterFilledFilter::CheckParam(doc_, e, kvp.Key, false);
			if(filterValue != kvp.Value) {
				flagControl = false;
				break;
			}
		}

		if(!flagControl) continue;

		Elements::BaseElement^ element = gcnew Elements::BaseElement();
		element->SetId(e->Id->IntegerValue);
		element->SetName(e->Name);
		element->SetCategoryName(e->Category->Name);
		element->SetBuiltInCategory(static_cast<BuiltInCategory>(e->Category->Id->IntegerValue).ToString());

		for each (String^ p in parameters) {
			String^ filterValue = Filters::ParameterFilledFilter::CheckParam(doc_, e, p, true);

			Elements::Parameter^ param = gcnew Elements::Parameter();
			param->_name = p;
			param->_value = filterValue;
			if(filterValue == nullptr) param->_filled = false;
			element->SetParameters(param);
		}
		elements_->Add(element);
	}
}

List<Elements::BaseElement^>^ Services::BaseService::GetElemenst() {
	return elements_;
}
*/