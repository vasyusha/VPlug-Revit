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

}//namespace Parameters

}//namespace MyDomain