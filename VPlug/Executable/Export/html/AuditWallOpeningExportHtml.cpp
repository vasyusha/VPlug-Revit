#include "../../../Headers/Export/html/AuditWallOpeningExportHtml.h"

namespace ExportHtml {

namespace WallOpening {

String^ DataOpening::Name::get() {
	return name_;
}

void DataOpening::Name::set(String^ value) {
	name_ = value;
}

int DataOpening::Id::get() {
	return id_;
}

void DataOpening::Id::set(int value) {
	id_ = value;
}

String^ DataOpening::CategoryName::get() {
	return categoryName_;
}

void DataOpening::CategoryName::set(String^ value) {
	categoryName_ = value;
}

String^ ReportElementWall::Name::get() {
	return name_;	
}

void ReportElementWall::Name::set(String^ value) {
	name_ = value;
}

int ReportElementWall::Id::get() {
	return id_;
}

void ReportElementWall::Id::set(int value) {
	id_ = value;	
}

String^ ReportElementWall::CategoryName::get() {
	return categoryName_;
}

void ReportElementWall::CategoryName::set(String^ value) {
	categoryName_ = value;
}

double ReportElementWall::Area::get() {
	return area_;
}

void ReportElementWall::Area::set(double value) {
	area_ = value;
}

int ReportElementWall::CountOpening::get() {
	return countOpening_;
}

void ReportElementWall::CountOpening::set(int value) {
	countOpening_ = value;
}

IList<DataOpening^>^ ReportElementWall::DataOpenings::get() {
	return dataOpenings_;
}

void ReportElementWall::DataOpenings::set(IList<DataOpening^>^ value) {
	dataOpenings_ = value;
}


String^ ReportTypeWall::Name::get() {
	return name_;
}

void ReportTypeWall::Name::set(String^ value) {
	name_ = value;
}

int ReportTypeWall::TotalWalls::get() {
	return totalWalls_;
}

void ReportTypeWall::TotalWalls::set(int value) {
	totalWalls_ = value;
}

double ReportTypeWall::TotalArea::get() {
	return totalArea_;
}

void ReportTypeWall::TotalArea::set(double value) {
	totalArea_ = value;
}

int ReportTypeWall::TotalOpening::get() {
	return totalOpening_;
}

void ReportTypeWall::TotalOpening::set(int value) {
	totalOpening_ = value;
}

double ReportTypeWall::TotalAreaWallsWithOpenings::get() {
	return totalAreaWallsWithOpenings_;
}

void ReportTypeWall::TotalAreaWallsWithOpenings::set(double value) {
	totalAreaWallsWithOpenings_ = value;
}

double ReportTypeWall::TotalAreaWallsWithoutOpenings::get() {
	return totalAreaWallsWithoutOpenings_;
}

void ReportTypeWall::TotalAreaWallsWithoutOpenings::set(double value) {
	totalAreaWallsWithoutOpenings_ = value;
}

ReportModel::ReportModel() {
	DataTypeWall = gcnew List<ReportTypeWall^>();
	DataElementWall = gcnew List<ReportElementWall^>();
}

String^ ReportModel::FilePath::get() {
	return filePath_;
}

void ReportModel::FilePath::set(String^ value) {
	filePath_ = value;
}

String^ ReportModel::ProjectName::get() {
	return projectName_;
}

void ReportModel::ProjectName::set(String^ value) {
	projectName_ = value;
}

String^ ReportModel::DataTimeStr::get() {
	return dataTimeStr_;
}

void ReportModel::DataTimeStr::set(String^ value) {
	dataTimeStr_ = value;
}

IList<ReportTypeWall^>^ ReportModel::DataTypeWall::get() {
	return typeWall_;
}

void ReportModel::DataTypeWall::set(IList<ReportTypeWall^>^ value) {
	typeWall_ = value;
}

IList<ReportElementWall^>^ ReportModel::DataElementWall::get() {
	return elemetnWall_;
}

void ReportModel::DataElementWall::set(IList<ReportElementWall^>^ value) {
	elemetnWall_ = value;
}

String^ AuditWallOpeningExportHtml::BuildHtml(ReportModel^ model) {
	if (model == nullptr)
		throw gcnew ArgumentNullException("model");

	StringBuilder^ sb = gcnew StringBuilder();

	AppendHeader(sb, model);

	return sb->ToString();
}

void AuditWallOpeningExportHtml::SaveHtmlToFile(ReportModel^ model, String^ path) {
	String^ html = BuildHtml(model);
	StreamWriter^ w = gcnew StreamWriter(path, false, System::Text::Encoding::UTF8);
	w->Write(html);
	w->Close();
}

void AuditWallOpeningExportHtml::AppendHeader(StringBuilder^ sb, ReportModel^ model) {
	sb->AppendLine("<!doctype html>");
	sb->AppendLine("<html lang=\"ru\">");
	sb->AppendLine("<head>");
	sb->AppendLine("	<meta charset=\"utf-8\"/>");
	sb->AppendLine("	<title>Отче: Кол-во проёмов в стене</title>");
	sb->AppendLine("	<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"/>");
	sb->AppendLine("	<style>");
	sb->AppendLine("		table {");
	sb->AppendLine("			width: 100%;");
	sb->AppendLine("			border-spacing: 0;");
	sb->AppendLine("		}");
	sb->AppendLine("		thead th {");
	sb->AppendLine("			border: 2px solid #bfb6c9;");
	sb->AppendLine("		}");
	sb->AppendLine("		tbody td {");
	sb->AppendLine("			padding: 10px 12px;");
	sb->AppendLine("			vertical-alling: top;");
	sb->AppendLine("			border: 2px solid #bfb6c9;");
	sb->AppendLine("		}");
	sb->AppendLine("	</style>");
	sb->AppendLine("</head>");

	AppendBody(sb, model);


	sb->AppendLine("</html>");
}

void AuditWallOpeningExportHtml::AppendBody(StringBuilder^ sb, ReportModel^ model) {
	sb->AppendLine("<body>");
	sb->AppendLine("	<header>");
	sb->AppendLine("		<h1>VPlug - отчет кол-во проёмов в стенах</h1>");
	sb->AppendLine("		<div>");
	sb->AppendLine("			<p>Файл:<span>" + model->ProjectName + "</span></p>");
	sb->AppendLine("			<p>Дата:<span>" + model->DataTimeStr + "</span></p>");
	sb->AppendLine("		</div>");
	sb->AppendLine("	</header>");
	sb->AppendLine("	<hr>");

	sb->AppendLine("	<table>");
	sb->AppendLine("		<thead>");
	sb->AppendLine("			<th>Имя типа</th>");
	sb->AppendLine("			<th>Кол-во элементов</th>");
	sb->AppendLine("			<th>Сумма площадей</th>");
	sb->AppendLine("			<th>Сумма площадей с проёмами</th>");
	sb->AppendLine("			<th>Сумма площадей без проёмов</th>");
	sb->AppendLine("			<th>Кол-во проёмов</th>");
	sb->AppendLine("			<th>Информация по проёму</th>");
	sb->AppendLine("		</thead>");
	sb->AppendLine("		<tbody>");

	for each (ReportTypeWall^ rtw in model->DataTypeWall) {
		sb->AppendLine("			<td>" + rtw->Name + "</td>");
		sb->AppendLine("			<td>" + rtw->TotalWalls + "</td>");
		sb->AppendLine("			<td>" + rtw->TotalArea.ToString("F3") + "</td>");
		sb->AppendLine("			<td>" + rtw->TotalAreaWallsWithOpenings.ToString("F3") + "</td>");
		sb->AppendLine("			<td>" + rtw->TotalAreaWallsWithoutOpenings.ToString("F3") + "</td>");
		sb->AppendLine("			<td>" + rtw->TotalOpening + "</td>");
		sb->AppendLine("			<td>В работе. ТЕСТ</td>");
	}

	sb->AppendLine("		</tbody>");
	sb->AppendLine("	</table>");
	sb->AppendLine("	</body>");

}

}//namespace WallOpening

}//namespace ExportHtml