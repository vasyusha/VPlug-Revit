#include "..\..\..\Headlines\Revit\Services\BaseService.h"

Services::BaseService::BaseService(Document^ doc, int category_id, List<String^>^ parameters) 
	: doc_(doc) {
	
	Filters::ElementCollectorFilter^ collector = gcnew Filters::ElementCollectorFilter(doc, category_id);
	List<Element^>^ elements = collector->FindElements();

}