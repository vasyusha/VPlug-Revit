#include "../../Headers/Domain/ParameterDomain.h"

namespace MyDomain {

namespace Parameters {

String^ Parameter::Name::get() {
	return name_;
}

void Parameter::Name::set(String^ value) {
	name_ = value;
}

String^ Parameter::Value::get() {
	return value_;
}

void Parameter::Value::set(String^ value) {
	value_ = value;
}

bool Parameter::Filled::get() {
	return filled_;
}

void Parameter::Filled::set(bool value) {
	filled_ = value;
}

ParameterStatus Parameter::Status::get() {
	return status_;
}

void Parameter::Status::set(ParameterStatus value) {
	status_ = value;
}

namespace Audit {

String^ Group::Name::get() {
	return name_;
}

void Group::Name::set(String^ value) {
	name_ = value;
}

bool Group::Pass::get() {
	return pass_;
}

void Group::Pass::set(bool value) {
	pass_ = value;
}

int Group::TotalElements::get() {
	return totalElements_;
}

void Group::TotalElements::set(int value) {
	totalElements_ = value;
}

int Group::PassElements::get() {
	return passElements_;
}

void Group::PassElements::set(int value) {
	passElements_ = value;
}

int Group::FailElements::get() {
	return failElements_;
}

void Group::FailElements::set(int value) {
	failElements_ = value;
}

int Group::TotalParams::get() {
	return totalParams_;
}

void Group::TotalParams::set(int value) {
	totalParams_ = value;
}

int Group::PassParams::get() {
	return passParams_;
}

void Group::PassParams::set(int value) {
	passParams_ = value;
}

int Group::MissingParams::get() {
	return missingParams_;
}

void Group::MissingParams::set(int value) {
	missingParams_ = value;
}

int Group::NoParams::get() {
	return noParams_;
}

void Group::NoParams::set(int value) {
	noParams_ = value;
}

int Group::Percent::get() {
	return percent_;	
}

void Group::Percent::set(int value) {
	if (value < 0) value = 0;
	if (value > 100) value = 100;
	percent_ = value;
}

Result::Result() {
	this->Groups = gcnew List<Group^>();
}

bool Result::Pass::get() {
	return pass_;
}

void Result::Pass::set(bool value) {
	pass_ = value;
}

int Result::GroupPass::get() {
	return groupPass_;
}

void Result::GroupPass::set(int value) {
	groupPass_ = value;
}

int Result::GroupTotal::get() {
	return groupTotal_;
}

void Result::GroupTotal::set(int value) {
	groupTotal_ = value;
}

int Result::ReqElementPass::get() {
	return reqElementPass_;
}

void Result::ReqElementPass::set(int value) {
	reqElementPass_ = value;
}

int Result::ReqElementTotal::get() {
	return reqElementTotal_;
}

void Result::ReqElementTotal::set(int value) {
	reqElementTotal_ = value;
}

int Result::ReqParamPass::get() {
	return reqParamPass_;
}

void Result::ReqParamPass::set(int value) {
	reqParamPass_ = value;
}

int Result::ReqParamTotal::get() {
	return reqParamTotal_;
}

void Result::ReqParamTotal::set(int value) {
	reqParamTotal_ = value;
}

int Result::Percent::get() {
	return percent_;
}

void Result::Percent::set(int value) {
	if (value < 0) value = 0;
	if (value > 100) value = 100;
	percent_ = value;
}

IList<Group^>^ Result::Groups::get() {
	return groups_;
}

void Result::Groups::set(IList<Group^>^ value) {
	groups_ = value;
}

}//namespace Audit

}//namespace Parameters

}//namespace MyDomain