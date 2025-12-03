#include "../../Headers/Domain/ElementDomain.h"

namespace MyDomain {

namespace Elements {

Element::Element() {
	this->Parameters = gcnew List<MyDomain::Parameters::Parameter^>();
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

IList<MyDomain::Parameters::Parameter^>^ Element::Parameters::get() {
	return parameters_;
}

void Element::Parameters::set(IList<MyDomain::Parameters::Parameter^>^ value) {
	parameters_ = value;
}

double WallElement::Area::get() {
	return area_;
}

void WallElement::Area::set(double value) {
	area_ = value;
}

bool WallElement::HasOpening::get() {
	return hasOpening_;
}

void WallElement::HasOpening::set(bool value) {
	hasOpening_ = value;
}

int WallElement::CountOpenings::get() {
	return countOpenings_;
}

void WallElement::CountOpenings::set(int value) {
	countOpenings_ = value;
}

IList<Element^>^ WallElement::LogicChildrenOpenings::get() {
	return logicChildrenOpenings_;
}

void WallElement::LogicChildrenOpenings::set(IList<Element^>^ value) {
	logicChildrenOpenings_ = value;
}

namespace AuditParameters {

MyDomain::Elements::Element^ AuditElement::Element::get() {
	return element_;
}

void AuditElement::Element::set(MyDomain::Elements::Element^ value) {
	element_ = value;
}

bool AuditElement::Pass::get() {
	return pass_;
}

void AuditElement::Pass::set(bool value) {
	pass_ = value;
}

int AuditElement::TotalParams::get() {
	return totalParams_;
}

void AuditElement::TotalParams::set(int value) {
	totalParams_ = value;
}

int AuditElement::PassParams::get() {
	return passParams_;
}

void AuditElement::PassParams::set(int value) {
	passParams_ = value;
}

int AuditElement::FailParams::get() {
	return failParams_;
}

void AuditElement::FailParams::set(int value) {
	failParams_ = value;
}

int AuditElement::FilledParams::get() {
	return filledParams_;
}

void AuditElement::FilledParams::set(int value) {
	filledParams_ = value;
}

int AuditElement::EmptyParams::get() {
	return emptyParams_;
}

void AuditElement::EmptyParams::set(int value) {
	emptyParams_ = value;
}

int AuditElement::MissingParams::get() {
	return missingParams_;
}

void AuditElement::MissingParams::set(int value) {
	missingParams_ = value;
}

int AuditElement::Percent::get() {
	return percent_;
}

void AuditElement::Percent::set(int value) {
	if (value < 0) value = 0;
	if (value > 100) value = 100;
	percent_ = value;
}

AuditGroup::AuditGroup() {
	this->Elements = gcnew List<AuditElement^>();
	this->CheckedParameters = gcnew List<String^>();
}

String^ AuditGroup::Name::get() {
	return name_;
}

void AuditGroup::Name::set(String^ value) {
	name_ = value;
}

bool AuditGroup::Pass::get() {
	return pass_;
}

void AuditGroup::Pass::set(bool value) {
	pass_ = value;
}

int AuditGroup::TotalElements::get() {
	return totalElements_;
}

void AuditGroup::TotalElements::set(int value) {
	totalElements_ = value;
}

int AuditGroup::PassElements::get() {
	return passElements_;
}

void AuditGroup::PassElements::set(int value) {
	passElements_ = value;
}

int AuditGroup::FailElements::get() {
	return failElements_;
}

void AuditGroup::FailElements::set(int value) {
	failElements_ = value;
}

int AuditGroup::TotalParams::get() {
	return totalParams_;
}

void AuditGroup::TotalParams::set(int value) {
	totalParams_ = value;
}

int AuditGroup::PassParams::get() {
	return passParams_;
}

void AuditGroup::PassParams::set(int value) {
	passParams_ = value;
}

int AuditGroup::FailParams::get() {
	return failParams_;
}

void AuditGroup::FailParams::set(int value) {
	failParams_ = value;
}

int AuditGroup::EmptyParams::get() {
	return emptyParams_;
}

void AuditGroup::EmptyParams::set(int value) {
	emptyParams_ = value;
}

int AuditGroup::MissingParams::get() {
	return missingParams_;
}

void AuditGroup::MissingParams::set(int value) {
	missingParams_ = value;
}

int AuditGroup::Percent::get() {
	return percent_;	
}

void AuditGroup::Percent::set(int value) {
	if (value < 0) value = 0;
	if (value > 100) value = 100;
	percent_ = value;
}

IList<AuditElement^>^ AuditGroup::Elements::get() {
	return elements_;
}

void AuditGroup::Elements::set(IList<AuditElement^>^ value) {
	elements_ = value;
}

IList<String^>^ AuditGroup::CheckedParameters::get() {
	return checkedParameters_;
}

void AuditGroup::CheckedParameters::set(IList<String^>^ value) {
	checkedParameters_ = value;
}

AuditResult::AuditResult() {
	this->Groups = gcnew List<AuditGroup^>();
}

bool AuditResult::Pass::get() {
	return pass_;
}

void AuditResult::Pass::set(bool value) {
	pass_ = value;
}

int AuditResult::TotalGroups::get() {
	return totalGroups_;
}

void AuditResult::TotalGroups::set(int value) {
	totalGroups_ = value;
}

int AuditResult::PassGroups::get() {
	return passGroups_;
}

void AuditResult::PassGroups::set(int value) {
	passGroups_ = value;
}

int AuditResult::FailGroup::get() {
	return failGrpups_;
}

void AuditResult::FailGroup::set(int value) {
	failGrpups_ = value;
}

int AuditResult::ReqElementPass::get() {
	return reqElementPass_;
}

void AuditResult::ReqElementPass::set(int value) {
	reqElementPass_ = value;
}

int AuditResult::ReqElementTotal::get() {
	return reqElementTotal_;
}

void AuditResult::ReqElementTotal::set(int value) {
	reqElementTotal_ = value;
}

int AuditResult::ReqParamPass::get() {
	return reqParamPass_;
}

void AuditResult::ReqParamPass::set(int value) {
	reqParamPass_ = value;
}

int AuditResult::ReqParamTotal::get() {
	return reqParamTotal_;
}

void AuditResult::ReqParamTotal::set(int value) {
	reqParamTotal_ = value;
}

int AuditResult::Percent::get() {
	return percent_;
}

void AuditResult::Percent::set(int value) {
	if (value < 0) value = 0;
	if (value > 100) value = 100;
	percent_ = value;
}

IList<AuditGroup^>^ AuditResult::Groups::get() {
	return groups_;
}

void AuditResult::Groups::set(IList<AuditGroup^>^ value) {
	groups_ = value;
}

}//namespace AuditParameters

}//namespace Elements

}//namespace MyDomain