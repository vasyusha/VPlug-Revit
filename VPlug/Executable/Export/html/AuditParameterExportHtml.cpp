#include "../../../Headers/Export/html/AuditParameterExportHtml.h"

namespace ExportHtml {

RequirementRow::RequirementRow() {
	Rows = gcnew List<Row^>();
}

CategoryReport::CategoryReport() {
	Requirements = gcnew List<RequirementRow^>();
}

String^ CategoryReport::Slug::get() {
	return slug_;
}

void CategoryReport::Slug::set(String^ value) {
	if (value != nullptr) {
		slug_ = value->Replace(' ', '_');
	} else {
		slug_ = nullptr;
	}
}

int CategoryReport::ChecksPass::get() {
	return checksPass_;
}

void CategoryReport::ChecksPass::set(int value) {
	checksPass_ = value;
}

int CategoryReport::ChecksTotal::get() {
	return checksTotal_;
}

void CategoryReport::ChecksTotal::set(int value) {
	checksTotal_ = value;
}

int CategoryReport::ElementsPass::get() {
	return elementsPass_;
}

void CategoryReport::ElementsPass::set(int value) {
	elementsPass_ = value;
}

int CategoryReport::ElementsTotal::get() {
	return elementsTotal_;
}

void CategoryReport::ElementsTotal::set(int value) {
	elementsTotal_ = value;
}

int CategoryReport::Percent::get() {
	return percent_;
}

void CategoryReport::Percent::set(int value) {
	if (value < 0) value = 0;
	if (value > 100) value = 100;
	percent_ = value;
}

ReportModel::ReportModel() {
	Categories = gcnew List<CategoryReport^>();
}

int ReportModel::ReqPass::get() {
	return reqPass_;
}

void ReportModel::ReqPass::set(int value) {
	reqPass_ = value;
}

int ReportModel::ReqTotal::get() {
	return reqTotal_;
}

void ReportModel::ReqTotal::set(int value) {
	reqTotal_ = value;
}

int ReportModel::CheckPass::get() {
	return checkPass_;
}

void ReportModel::CheckPass::set(int value) {
	checkPass_ = value;
}

int ReportModel::CheckTotal::get() {
	return checkTotal_;
}

void ReportModel::CheckTotal::set(int value) {
	checkTotal_ = value;
}

int ReportModel::ElPass::get() {
	return elPass_;
}

void ReportModel::ElPass::set(int value) {
	elPass_ = value;
}

int ReportModel::ElTotal::get() {
	return elTotal_;
}

void ReportModel::ElTotal::set(int value) {
	elTotal_ = value;
}

int ReportModel::Percent::get() {
	return percent_;
}

void ReportModel::Percent::set(int value) {
	if (value < 0) value = 0;
	if (value > 100) value = 100;
	percent_ = value;
}

}// namespace ExportHtml