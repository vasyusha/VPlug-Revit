#include "../../Headers/Domain/ReportDomain.h"

namespace MyDomain {

namespace AuditParameterReport {

ResultReport::ResultReport() {
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

MyDomain::Elements::AuditParameters::AuditResult^ ResultReport::Result::get() {
	return result_;
}

void ResultReport::Result::set(MyDomain::Elements::AuditParameters::AuditResult^ value) {
	result_ = value;
}

}//namespace AuditParameterReport 

}//namespace MyDomai