#include "..\..\..\Headers\Revit\Services\BaseService.h"

Services::BaseService::BaseService(Document^ doc, int category_id, List<String^>^ parameters) 
	: doc_(doc) {
	
	Filters::ElementCollectorFilter^ collector = gcnew Filters::ElementCollectorFilter(doc, category_id);
	List<Element^>^ elements = collector->FindElements();
	
	SetElements(elements, parameters);
}

Services::BaseService::BaseService(Document^ doc, Tuple<String^, String^>^ find_par_val, List<String^>^ parameters) 
	: doc_(doc) {

	FilteredElementCollector^ collector = gcnew FilteredElementCollector(doc);
	IList<Element^>^ model_element = collector->WhereElementIsNotElementType()->WhereElementIsViewIndependent()->ToElements();
	List<Element^>^ list = gcnew List<Element^>(model_element);

	SetElements(list, find_par_val, parameters);
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
			Filters::ParameterFilledFilter^ filter = gcnew Filters::ParameterFilledFilter();
			//А когда нужны все параметры?
			String^ filter_out = filter->CheckParam(doc_, e, param, true);

			if(filter_out != nullptr) {
				element->SetParameters(param, filter_out);
			}
		}
		elements_->Add(element);
	}
}

void Services::BaseService::SetElements(List<Element^>^ elements, Tuple<String^, String^>^ find_par_val, List<String^>^ parameters) {
	elements_ = gcnew List<Elements::BaseElement^>();

	for each(Element^ e in elements) {
		Filters::ParameterFilledFilter^ filter = gcnew Filters::ParameterFilledFilter();

		String^ filter_prarm = filter->CheckParam(doc_, e, find_par_val->Item1, false);

		if(filter_prarm == find_par_val->Item2) {
			Elements::BaseElement^ element = gcnew Elements::BaseElement();

			element->SetId(e->Id->IntegerValue);
			element->SetName(e->Name);
			element->SetCategoryName(e->Category->Name);
			element->SetBuiltInCategory(static_cast<BuiltInCategory>(e->Category->Id->IntegerValue).ToString());

			for each(String^ param in parameters) {
				Filters::ParameterFilledFilter^ filter2 = gcnew Filters::ParameterFilledFilter();
			//А когда нужны все параметры?
				String^ filter_out = filter2->CheckParam(doc_, e, param, true);

				if(filter_out != nullptr) {
					element->SetParameters(param, filter_out);
				}
			}
			elements_->Add(element);

		} else {
			continue;
		}
	}
}

List<Elements::BaseElement^>^ Services::BaseService::GetElemenst() {
	return elements_;
}