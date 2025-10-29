#include "../../../Headers/Export/html/AuditParameterExportHtml.h"

namespace ExportHtml {

RequirementRow::RequirementRow() {
	Params = gcnew List<Param^>();
}

CategoryReport::CategoryReport() {
	Requirements = gcnew List<RequirementRow^>();
	CheckedParameters = gcnew List<String^>();
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

int ReportModel::SpecPass::get() {
	return specPass_;
}

void ReportModel::SpecPass::set(int value) {
	specPass_ = value;
}

int ReportModel::SpecTotal::get() {
	return specTotal_;
}

void ReportModel::SpecTotal::set(int value) {
	specTotal_ = value;
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
	//if (value < 0) value = 0;
	//if (value > 100) value = 100;
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
	sb->AppendLine("	<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"/>");
	sb->AppendLine("	<style>");
	sb->AppendLine("		:root {");
	sb->AppendLine("			--bg: #f7f7f7;");
	sb->AppendLine("			--green: #97cc64;");
	sb->AppendLine("			--light-green: #b6cca1;");
	sb->AppendLine("			--red: #fb5a3e;");
	sb->AppendLine("			--light-red: #fbb4a8;");
	sb->AppendLine("		}");
	sb->AppendLine("		* {");
	sb->AppendLine("			box-sizing: border-box;");
	sb->AppendLine("		}");
	sb->AppendLine("		body { font-family: 'Arial', sans-serif; padding: 10px 40px; }");
	sb->AppendLine("		.pass { background-color: var(--green); }");
	sb->AppendLine("		.fail { background-color: var(--red); }");
	sb->AppendLine("		.percent {");
	sb->AppendLine("			text-align: left;");
	sb->AppendLine("			padding-top: 5px;");
	sb->AppendLine("			padding-left: 5px;");
	sb->AppendLine("			padding-bottom: 5px;");
	sb->AppendLine("			color: white;");
	sb->AppendLine("			border-radius:");
	sb->AppendLine("			5px; white-space: nowrap;");
	sb->AppendLine("		}");
	sb->AppendLine("		span.item {");
	sb->AppendLine("			padding: 5px;");
	sb->AppendLine("			border-radius: 5px;");
	sb->AppendLine("			margin-right: 5px;");
	sb->AppendLine("			border: 1px solid #eee;");
	sb->AppendLine("			font-size: 0.6em;");
	sb->AppendLine("		}");
	sb->AppendLine("		span.item.pass, span.item.fail {");
	sb->AppendLine("			color: #FFF;");
	sb->AppendLine("			font-weight: bold;");
	sb->AppendLine("			border: 0px;");
	sb->AppendLine("		}");
	sb->AppendLine("		section {");
	sb->AppendLine("			padding: 15px;");
	sb->AppendLine("			border-radius: 5px;");
	sb->AppendLine("			border: 1px solid #eee;");
	sb->AppendLine("			margin-bottom: 15px;");
	sb->AppendLine("		}");
	sb->AppendLine("		div.info {");
	sb->AppendLine("			float: left;");
	sb->AppendLine("			width: 30%;");
	sb->AppendLine("		}");
	sb->AppendLine("		div.results {");
	sb->AppendLine("			float: left;");
	sb->AppendLine("			width: calc(70% - 20px);");
	sb->AppendLine("			margin-left: 20px;");
	sb->AppendLine("			padding: 20px;");
	sb->AppendLine("			border-radius: 5px;");
	sb->AppendLine("			background-color: #fafafa;");
	sb->AppendLine("		}");
	sb->AppendLine("	</style>");
	sb->AppendLine("</head>");
	
	AppendBody(sb, model);
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
	sb->AppendLine("			Спецификации пройдены: <strong>" + model->SpecPass+ "</strong>/<strong>" + model->SpecTotal+ "</strong>");
	sb->AppendLine("		</span>");
	sb->AppendLine("		<span class=\"item\">");
	sb->AppendLine("			Требования приняты: <strong>" + model->ReqPass+ "</strong>/<strong>" + model->ReqTotal+ "</strong>");
	sb->AppendLine("		</span>");
	sb->AppendLine("		<span class=\"item\">");
	sb->AppendLine("			Проверки пройдены: <strong>" + model->CheckPass + "</strong>/<strong>" + model->CheckTotal + "</strong>");
	sb->AppendLine("		</span>");
	sb->AppendLine("	</p>");
	sb->AppendLine("	<hr>");

	AppendSection(sb, model);

	sb->AppendLine("</body>");
	sb->AppendLine("</html>");

}

void AuditParameterExportHtml::AppendSection(StringBuilder^ sb, ReportModel^ model) {
	int numCategory = 1;
	for each (CategoryReport^ cr in model->Categories) {
		sb->AppendLine("	<section style=\"clear: both; overflow: hidden; \">");
		sb->AppendLine("		<div class=\"info\">");
		sb->AppendLine("			<h2>" + numCategory + ". " + cr->Name + "</h2>");	
		sb->AppendLine("			<div class=\"container\">");

		String^ passOrFailed = cr->ChecksPass == cr->ChecksTotal ? "pass" : "fail";

		sb->AppendLine("				<div class=\"" + passOrFailed + " percent\" style=\"width: " + cr->Percent + ";\">" + cr->Percent +"%</div>");
		sb->AppendLine("			</div>");

		String^ RuPassOrFailed = passOrFailed == "pass" ? "Успех" : "Ошибки";

		sb->AppendLine("			<p><span class=\"item" + passOrFailed + "\">" + RuPassOrFailed + "</span></p>");
		sb->AppendLine("			<p><span class=\"item\">Проверки пройдены <strong>" + cr->ChecksPass + "</strong>/<strong>" + cr->ChecksTotal + "</strong></span></p>");
		sb->AppendLine("			<p><span class=\"item\">Элементы прошли<strong>" + cr->ElementsPass+ "</strong>/<strong>" + cr->ElementsTotal+ "</strong></span></p>");
		sb->AppendLine("		</div>");	
		sb->AppendLine("		<div class=\"results\">");
		sb->AppendLine("			<p><strong>Применимо</strong></p>");
		sb->AppendLine("			<ul>");
		sb->AppendLine("				<li>" + cr->Slug + "</li>");	
		sb->AppendLine("			</ul>");
		sb->AppendLine("			<p><strong>Требования</strong></p>");
		sb->AppendLine("			<p><span>Заполнение параметров</span>");
		sb->AppendLine("			<ul>");
	
		for each (String^ p in cr->CheckedParameters) {
			sb->AppendLine("				<li>" + p + "</li>");
		}

		sb->AppendLine("			</ul>");
		sb->AppendLine("			<hr>");
		sb->AppendLine("			<p><span>Данные по элементам</span></p>");
		sb->AppendLine("				<details>");
		sb->AppendLine("					<summary>Таблица всех элементов по группе</summary>");
		sb->AppendLine("				<table class=\"" + passOrFailed + "\">");
		sb->AppendLine("					<thead>");
		sb->AppendLine("						<tr>");
		sb->AppendLine("							<th>Id</th>");
		sb->AppendLine("							<th>Имя</th>");
		sb->AppendLine("							<th>Параметры</th>");
		sb->AppendLine("						</tr>");
		sb->AppendLine("					</thead>");
		sb->AppendLine("					<tbody>");

		for each (RequirementRow^ r in cr->Requirements) {
			sb->AppendLine("						<tr>");
			sb->AppendLine("							<th>" + r->Id + "</th>");
			sb->AppendLine("							<th>" + r->Name+ "</th>");
			sb->AppendLine("							<th>");

			for each (RequirementRow::Param^ p in r->Params) {
				sb->AppendLine("								" + p->Name);
			}

			sb->AppendLine("							</th>");
			sb->AppendLine("						</tr>");
		}

		sb->AppendLine("					</tbody>");
		sb->AppendLine("				</table>");
		sb->AppendLine("				</details>");
		sb->AppendLine("			<hr>");
		/*
		sb->AppendLine("			p><span>Данные по параметрам</span></p>");
		sb->AppendLine("			<ol>");
		sb->AppendLine("				<li>");
		sb->AppendLine("					<details>");

		sb->AppendLine("					</details>");
		sb->AppendLine("				</li>");
		sb->AppendLine("			</ol>");
		*/
		sb->AppendLine("	</section>");
		++numCategory;	
	}
}



}// namespace ExportHtml