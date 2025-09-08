#include "..\..\..\Headlines\Revit\Filters\ElementCollectorFilter.h"

Filters::ElementCollectorFilter::ElementCollectorFilter(Document^ doc, BuiltInCategory category) 
	: doc_(doc), category_(category) {

	class_type_ = nullptr;
	category_id_ = nullptr;
}

Filters::ElementCollectorFilter::ElementCollectorFilter(Document^ doc, Type^ class_type) : doc_(doc)
	,class_type_(class_type) {
	
	category_id_ = nullptr;
}

Filters::ElementCollectorFilter::ElementCollectorFilter(Document^ doc, int category_id) : doc_(doc) {
	
	class_type_ = nullptr;
	category_id_ = gcnew ElementId(category_id);
}

List<Element^>^ Filters::ElementCollectorFilter::FindElements() {
	List<Element^>^ result = gcnew List<Element^>();

	FilteredElementCollector^ collector = gcnew FilteredElementCollector(doc_);

	if(class_type_ != nullptr) {
		collector->OfClass(class_type_);
	} else if(category_id_ != nullptr) {
		collector->OfCategoryId(category_id_);
	} else {
		collector->OfCategory(category_);
	}

	collector->WhereElementIsNotElementType();

	for each(Element^ e in collector) {
		result->Add(e);
	}

	return result;
}

