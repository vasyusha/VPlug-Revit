#include "..\..\..\Headers\Revit\Services\BaseService.h"

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

		for each(String^ param in parameters) {
			//А когда нужны все параметры?
			String^ filter_out = Filters::ParameterFilledFilter::CheckParam(doc_, e, param, true);

			if(filter_out != nullptr) {
				element->SetParameters(param, filter_out);
			}
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
			if (filterValue == nullptr) continue;

			element->SetParameters(p, filterValue);
		}
		
		elements_->Add(element);
	}
}

List<Elements::BaseElement^>^ Services::BaseService::GetElemenst() {
	return elements_;
}