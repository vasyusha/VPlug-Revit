#include "..\..\..\Headers\Revit\Elements\BaseElement.h"

namespace Elements {

BaseElement::BaseElement() {
	parameters_ = gcnew List<ParamResult^>();
}

int BaseElement::Id::get() {
	return id_;
}

void BaseElement::Id::set(int value) {
	id_ = value;
}

String^ BaseElement::UniqueId::get() {
	return uniqueId_;
}

void BaseElement::UniqueId::set(String^ value) {
	uniqueId_ = value;	
}

String^ BaseElement::Name::get() {
	return name_;
}

void BaseElement::Name::set(String^ value) {
	name_ = value;
}

String^ BaseElement::CategoryName::get() {
	return categoryName_;	
}

void BaseElement::CategoryName::set(String^ value) {
	categoryName_ = value;
}

int BaseElement::BuiltInCategory::get() {
	return builtInCategory_;
}

void BaseElement::BuiltInCategory::set(int value) {
	builtInCategory_ = value;
}

String^ BaseElement::BuiltInCategoryName::get() {
	return builtInCategoryName_;
}

void BaseElement::BuiltInCategoryName::set(String^ value) {
	builtInCategoryName_ = value;
}

void BaseElement::AddParameter(String^ name, String^ value, bool filled) {
	auto p = gcnew ParamResult();
	p->Name = name;
	p->Value = value;
	p->Filled = filled;
	parameters_->Add(p);
}

IList<ParamResult^>^ BaseElement::Parameters::get() {
	 return parameters_;
};

}
