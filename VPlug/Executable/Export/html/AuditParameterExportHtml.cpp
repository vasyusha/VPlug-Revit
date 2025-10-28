#include "../../../Headers/Export/html/AuditParameterExportHtml.h"

namespace ExportHtml {

RequirementRow::RequirementRow() {
	Params = gcnew List<Param^>();
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

String^ AuditParameterExportHtml::BuildHtml(ReportModel^ model) {
	if (model == nullptr)
		throw gcnew ArgumentNullException("model");

	StringBuilder^ sb = gcnew StringBuilder();

	AppendHeader(sb, model);

	return sb->ToString();
}

void AuditParameterExportHtml::SaveHtmlToFile(ReportModel^ model, String^ path) {
	String^ html = BuildHtml(model);
	StreamWriter^ w = gcnew StreamWriter(path, false, System::Text::Encoding::UTF8);
	w->Write(html);
	w->Close();
}

void AuditParameterExportHtml::AppendHeader(StringBuilder^ sb, ReportModel^ model) {
	sb->AppendLine("<!doctype html>");
	sb->AppendLine("<html lang=\"ru\">");
	sb->AppendLine("<head>");
	sb->AppendLine("	<meta charset=\"utf-8\"/>");
	sb->AppendLine("	<title>Отче: заполнение параметров</title>");
	sb->AppendLine("	<meta name=\"viewport\" content=\"width = device - width, initial - scale = 1\"/>");
	sb->AppendLine("	<style>");
	sb->AppendLine("		:root {");
	sb->AppendLine("			--bg: #f7f7f7;");
	sb->AppendLine("			--green: #97cc64;");
	sb->AppendLine("			--light-green: #b6cca1;");
	sb->AppendLine("			--red: #fb5a3e;");
	sb->AppendLine("			--light-red: #fbb4a8;");
	sb->AppendLine("		}");
	sb->AppendLine("	</style>");
	sb->AppendLine("</head>");
}


void AuditParameterExportHtml::AppendBody(StringBuilder^ sb, ReportModel^ model) { 
	sb->AppendLine("<body>");
	sb->AppendLine("	<header>");
	sb->AppendLine("		<h1>Vplug - отчет по параметрам</h1>");
	sb->AppendLine("		<div>");
	sb->AppendLine("			<p>Файл:<span>" + model->ProjectName + "</span></p>");
	sb->AppendLine("			<p>Дата:<span>" + model->DataTimeStr + "</span></p>");
	sb->AppendLine("		</div>");
	sb->AppendLine("	</header>");
	sb->AppendLine("	<hr>");
	sb->AppendLine("	<h2>Краткое содержание<h2>");
	String^ passOrFailed = model->ReqPass == model->ReqPass ? "pass" : "fail";
	sb->AppendLine("	<div class=\"" + passOrFailed + " percent\" style=\"width: " + model->Percent + ";\">" + model->Percent +"%</div>");
	sb->AppendLine("	<p>");
	String^ RuPassOrFailed = passOrFailed == "pass" ? "Успех" : "Ошибки";
	sb->AppendLine("		<span class=\"item pass\">" + RuPassOrFailed + "</span>");
	sb->AppendLine("		<span class=\"item\">");
	sb->AppendLine("			Спецификации пройдены: <strong>" + model->ReqPass + "</strong>/<strong>" + model->ReqTotal + "</strong>");
	sb->AppendLine("		</span>");
	sb->AppendLine("		<span class=\"item\">");
	sb->AppendLine("			Требования приняты: <strong>" + model->ElPass + "</strong>/<strong>" + model->ElTotal + "</strong>");
	sb->AppendLine("		</span>");
	sb->AppendLine("		<span class=\"item\">");
	sb->AppendLine("			Проверки пройдены: <strong>" + model->CheckPass + "</strong>/<strong>" + model->CheckTotal + "</strong>");
	sb->AppendLine("		</span>");
	sb->AppendLine("	</p>");
	sb->AppendLine("	<hr>");

	sb->AppendLine("</body>");
}




}// namespace ExportHtml