#include "../../Headers/Domain/ReportDomain.h"

namespace MyDomain {

namespace Reports {

namespace Elements {

MyDomain::Elements::Element^ ElementReport::Element::get() {
	return element_;
}

void ElementReport::Element::set(MyDomain::Elements::Element^ value) {
	element_ = value;
}

GroupReport::GroupReport() {
	this->Elements = gcnew List<ElementReport^>();
	this->CheckedParameters = gcnew List<String^>();
};

MyDomain::Parameters::Audit::Group^ GroupReport::Group::get() {
	return group_;
}

void GroupReport::Group::set(MyDomain::Parameters::Audit::Group^ value) {
	group_ = value;
}

IList<ElementReport^>^ GroupReport::Elements::get() {
	return elements_;
}

void GroupReport::Elements::set(IList<ElementReport^>^ value) {
	elements_ = value;
}

IList<String^>^ GroupReport::CheckedParameters::get() {
	return checkedParameters_;
}

void GroupReport::CheckedParameters::set(IList<String^>^ value) {
	checkedParameters_ = value;
}

ResultReport::ResultReport() {
	this->Groups = gcnew List<GroupReport^>();
}

String^ ResultReport::FilePath::get() {
	return filePath_;
}

void ResultReport::FilePath::set(String^ value) {
	filePath_ = value;
}

String^ ResultReport::ProjectName::get() {
	return projectName_;
}

void ResultReport::ProjectName::set(String^ value) {
	projectName_ = value;
}

String^ ResultReport::DateTimeStr::get() {
	return dateTimeStr_;
}

void ResultReport::DateTimeStr::set(String^ value) {
	dateTimeStr_ = value;
}

IList<GroupReport^>^ ResultReport::Groups::get() {
	return groups_;
}

void ResultReport::Groups::set(IList<GroupReport^>^ value) {
	groups_ = value;
}

MyDomain::Parameters::Audit::Result^ ResultReport::Result::get() {
	return result_;
}

void ResultReport::Result::set(MyDomain::Parameters::Audit::Result^ value) {
	result_ = value;
}

}//namespace Elements

}//namespace Reports

}//namespace MyDomain