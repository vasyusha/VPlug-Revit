#include "../../Headers/Domain/ElementDomain.h"

namespace MyDomain {

namespace Elements {

Element::Element() {
	this->Param = gcnew List<Parameters::Parameter^>();
}

int Element::Id::get() {
	return id_;
}

void Element::Id::set(int value) {
	id_ = value;
}

String^ Element::UniqueId::get() {
	return uniqueId_;
}

void Element::UniqueId::set(String^ value) {
	uniqueId_ = value;
}

String^ Element::Name::get() {
	return name_;
}

void Element::Name::set(String^ value) {
	name_ = value;
}

String^ Element::CategoryName::get() {
	return categoryName_;
}

void Element::CategoryName::set(String^ value) {
	categoryName_ = value;
}

int Element::BuiltInCategory::get() {
	return builtInCategory_;
}

void Element::BuiltInCategory::set(int value) {
	builtInCategory_ = value;
}

String^ Element::BuiltInCategoryName::get() {
	return builtInCategoryName_;
}

void Element::BuiltInCategoryName::set(String^ value) {
	builtInCategoryName_ = value;
}

IList<Parameters::Parameter^>^ Element::Param::get() {
	return parameters_;
}

void Element::Param::set(IList<Parameters::Parameter^>^ value) {
	parameters_ = value;
}

}//namespace Elements

}//namespace MyDomain