#include "..\..\..\Headlines\Revit\Elements\BaseElement.h"

void Elements::BaseElement::SetId(String^ id) {
	id_ = id;
}
String^ Elements::BaseElement::GetId() {
	return id_;
}

void Elements::BaseElement::SetName(String^ name) {
	name_ = name;
}
String^ Elements::BaseElement::GetName() {
	return name_;
}

void Elements::BaseElement::SetGuid(String^ guid) {
	guid_ = guid;
}
String^ Elements::BaseElement::GetGuid() {
	return guid_;
}

void Elements::BaseElement::SetCategory(String^ category) {
	category_ = category;
}

String^ Elements::BaseElement::GetCategory() {
	return category_;
}

void Elements::BaseElement::SetParameters(String^ key, String^ value) {
	if(parameters_ == nullptr) {
		parameters_ = gcnew Dictionary<String^, String^>();
	}

	if(key != nullptr && value != nullptr) {
		parameters_->Add(key, value);
	}
}
Dictionary<String^, String^>^ Elements::BaseElement::GetParameters() {
	return parameters_;
}

