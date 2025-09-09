#include "..\..\..\Headlines\Revit\Services\BaseService.h"

Services::BaseService::BaseService(Document^ doc, int category_id, List<String^>^ parameters) 
	: doc_(doc) {
	
	Filters::ElementCollectorFilter^ collector = gcnew Filters::ElementCollectorFilter(doc, category_id);
	List<Element^>^ elements = collector->FindElements();
	
	SetElements(elements, parameters);
}

void Services::BaseService::SetElements(List<Element^>^ elements, List<String^>^ parameters) {
	elements_ = gcnew List<Elements::BaseElement^>();

	for each(Element^ e in elements) {
		Elements::BaseElement^ element = gcnew Elements::BaseElement();

		element->SetId(e->Id->IntegerValue.ToString());
		element->SetName(e->Name);

		for each(String^ param in parameters) {
			Filters::ParameterFilledFilter^ filter = gcnew Filters::ParameterFilledFilter();
			String^ filter_out = filter->CheckParam(doc_, e, param);

			if(filter_out != nullptr) {
				element->SetParameters(param, filter_out);
			}
		}
		elements_->Add(element);
	}
}

List<Elements::BaseElement^>^ Services::BaseService::GetElemenst() {
	return elements_;
}