#include "../../../Headers/Export/html/AuditWallOpeningExportHtml.h"

namespace ExportHtml {

String^ AuditWallOpeningExportHtml::BuildHtml(MyDomain::WallOpening::WallOpeningReport^ report) {
	if (report == nullptr)
		throw gcnew ArgumentNullException("model");

	StringBuilder^ sb = gcnew StringBuilder();

	AppendHeader(sb, report);

	return sb->ToString();
}

void AuditWallOpeningExportHtml::SaveHtmlToFile(MyDomain::WallOpening::WallOpeningReport^ report, String^ path) {
	String^ html = BuildHtml(report);
	StreamWriter^ w = gcnew StreamWriter(path, false, System::Text::Encoding::UTF8);
	w->Write(html);
	w->Close();
}

void AuditWallOpeningExportHtml::AppendHeader(StringBuilder^ sb, MyDomain::WallOpening::WallOpeningReport^ report) {
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

	AppendBody(sb, report);


	sb->AppendLine("</html>");
}

void AuditWallOpeningExportHtml::AppendBody(StringBuilder^ sb, MyDomain::WallOpening::WallOpeningReport^ report) {
	sb->AppendLine("<body>");
	sb->AppendLine("	<header>");
	sb->AppendLine("		<h1>VPlug - отчет кол-во проёмов в стенах</h1>");
	sb->AppendLine("		<div>");
	sb->AppendLine("			<p>Файл:<span>" + report->ProjectName + "</span></p>");
	sb->AppendLine("			<p>Дата:<span>" + report->DateTimeStr + "</span></p>");
	sb->AppendLine("		</div>");
	sb->AppendLine("	</header>");
	sb->AppendLine("	<hr>");
	sb->AppendLine("	<h3>По типу</h3>");

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

	for each (KeyValuePair<String^, MyDomain::WallOpening::WallTypeInfo^> kvp in report->WallTypes) {
		sb->AppendLine("			<tr>");
		sb->AppendLine("				<td>" + kvp.Value->Name + "</td>");
		sb->AppendLine("				<td>" + kvp.Value->TotalWalls + "</td>");
		sb->AppendLine("				<td>" + kvp.Value->TotalArea.ToString("F3") + "</td>");
		sb->AppendLine("				<td>" + kvp.Value->TotalAreaWallsWithOpenings.ToString("F3") + "</td>");
		sb->AppendLine("				<td>" + kvp.Value->TotalAreaWallsWithoutOpenings.ToString("F3") + "</td>");
		sb->AppendLine("				<td>" + kvp.Value->TotalOpenings + "</td>");
		sb->AppendLine("				<td>В работе. ТЕСТ</td>");
		sb->AppendLine("			</tr>");
	}

	sb->AppendLine("		</tbody>");
	sb->AppendLine("	</table>");
	sb->AppendLine("	<h3>По экземпляру</h3>");
	sb->AppendLine("	<table>");
	sb->AppendLine("		<thead>");
	sb->AppendLine("			<th>Id</th>");
	sb->AppendLine("			<th>Имя</th>");
	sb->AppendLine("			<th>Площадь</th>");
	sb->AppendLine("			<th>Кол-во проёмов</th>");
	sb->AppendLine("			<th>Информация по проёму</th>");
	sb->AppendLine("		</thead>");
	sb->AppendLine("		<tbody>");


	for each (MyDomain::WallOpening::WallElementInfo^ wallElement in report->WallElemnts) {
		sb->AppendLine("			<tr>");
		sb->AppendLine("				<td>" + wallElement->Name + "</td>");
		sb->AppendLine("				<td>" + wallElement->Id + "</td>");
		sb->AppendLine("				<td>" + wallElement->Area.ToString("F3") + "</td>");
		sb->AppendLine("				<td>" + wallElement->CountOpenings + "</td>");
		sb->AppendLine("				<td>");

		for each (MyDomain::WallOpening::OpeningInfo^ openingInfo in wallElement->Openings) {
			sb->AppendLine("					<p>Id: " + openingInfo->Id + "</p>");
			sb->AppendLine("					<p>Имя: " + openingInfo->Name + "</p>");
			sb->AppendLine("					<p>Категория: " + openingInfo->CategoryName + "</p>");
			sb->AppendLine("					<hr>");
		}

		sb->AppendLine("				</td>");
		sb->AppendLine("			</tr>");
	}

	sb->AppendLine("		</tbody>");
	sb->AppendLine("	</table>");
	sb->AppendLine("	</body>");
}

}//namespace ExportHtml