#include "../../../Headers/Export/html/AuditWallOpeningExportHtml.h"

namespace ExportHtml {

String^ AuditWallOpeningExportHtml::BuildHtml(MyDomain::AuditWallOpeningsReport::ResultReport^ resultReport) {
	if (resultReport == nullptr)
		throw gcnew ArgumentNullException("report");

	StringBuilder^ sb = gcnew StringBuilder();

	AppendHeader(sb, resultReport);

	return sb->ToString();
}

void AuditWallOpeningExportHtml::SaveHtmlToFile(MyDomain::AuditWallOpeningsReport::ResultReport^ resultReport, String^ path) {
	String^ html = BuildHtml(resultReport);
	StreamWriter^ w = gcnew StreamWriter(path, false, System::Text::Encoding::UTF8);
	w->Write(html);
	w->Close();
}

void AuditWallOpeningExportHtml::AppendHeader(StringBuilder^ sb, MyDomain::AuditWallOpeningsReport::ResultReport^ resultReport) {
	sb->AppendLine("<!doctype html>");
	sb->AppendLine("<html lang=\"ru\">");
	sb->AppendLine("<head>");
	sb->AppendLine("	<meta charset=\"utf-8\"/>");
	sb->AppendLine("	<title>Отче: Кол-во проёмов в стене</title>");
	sb->AppendLine("	<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"/>");
	sb->AppendLine("	<style>");
	sb->AppendLine("		* {");
	sb->AppendLine("			box-sizing: border-box;");
	sb->AppendLine("		}");
	sb->AppendLine("		body {");
	sb->AppendLine("			font-family: 'Arial', sans-serif;");
	sb->AppendLine("			padding: 10px 40px;");
	sb->AppendLine("		}");
	sb->AppendLine("		section {");
	sb->AppendLine("			padding: 15px;");
	sb->AppendLine("			border-radius: 5px;");
	sb->AppendLine("			border: 1px solid #eee;");
	sb->AppendLine("			margin-bottom: 15px;");
	sb->AppendLine("		}");
	sb->AppendLine("		table {");
	sb->AppendLine("			width: 100%;");
	sb->AppendLine("			border-collapse: collapse;");
	sb->AppendLine("			border-spacing: 0;");
	sb->AppendLine("		}");
	sb->AppendLine("		thead th {");
	sb->AppendLine("			border: 1px solid #bfb6c9;");
	sb->AppendLine("		}");
	sb->AppendLine("		tbody td {");
	sb->AppendLine("			padding: 10px 12px;");
	sb->AppendLine("			vertical-align: top;");
	sb->AppendLine("			border: 1px solid #bfb6c9;");
	sb->AppendLine("		}");
	sb->AppendLine("		span.data-row, div.data-row {");
	sb->AppendLine("			position: sticky;");
	sb->AppendLine("			top: 20px;");
	sb->AppendLine("			background: #fff;;");
	sb->AppendLine("			z-index: 1;");
	sb->AppendLine("		}");
	sb->AppendLine("		summary.opening-sum {");
	sb->AppendLine("			font-size: 16px;");
	sb->AppendLine("		}");
	sb->AppendLine("		td.opening-col {");
	sb->AppendLine("			font-size: 12px;");
	sb->AppendLine("		}");
	sb->AppendLine("		td.opening-col .opening {");
	sb->AppendLine("			padding: 4px 6px;");
	sb->AppendLine("			border-bottom: 1px dashed #ddd;");
	sb->AppendLine("			margin-bottom: 4px;");
	sb->AppendLine("		}");
	sb->AppendLine("		td.opening-col .opening:last-child {");
	sb->AppendLine("			border-bottom: none;");
	sb->AppendLine("			margin-bottom: 0;");
	sb->AppendLine("		}");
	sb->AppendLine("		td.opening-col .opening p {");
	sb->AppendLine("			margin: 0;");
	sb->AppendLine("		}");
	sb->AppendLine("		td.opening-col .opening p + p {");
	sb->AppendLine("			margin-top: 2px;");
	sb->AppendLine("		}");
	sb->AppendLine("	</style>");
	sb->AppendLine("</head>");

	AppendBody(sb, resultReport);


	sb->AppendLine("</html>");
}

void AuditWallOpeningExportHtml::AppendBody(StringBuilder^ sb, MyDomain::AuditWallOpeningsReport::ResultReport^ resultReport) {
	sb->AppendLine("<body>");
	sb->AppendLine("	<header>");
	sb->AppendLine("		<h1>VPlug - отчет кол-во проёмов в стенах</h1>");
	sb->AppendLine("		<div>");
	sb->AppendLine("			<p>Файл: <span>" + resultReport->ProjectName + "</span></p>");
	sb->AppendLine("			<p>Дата: <span>" + resultReport->DateTimeStr + "</span></p>");
	sb->AppendLine("		</div>");
	sb->AppendLine("	</header>");
	sb->AppendLine("	<hr>");
	sb->AppendLine("	<section>");
	sb->AppendLine("		<details>");
	sb->AppendLine("		<summary><strong>Отчет по группе</strong></summary>");
	sb->AppendLine("			<table>");
	sb->AppendLine("				<thead>");
	sb->AppendLine("					<tr>");
	sb->AppendLine("						<th>По фильтру</th>");
	sb->AppendLine("						<th>Кол-во элементов</th>");
	sb->AppendLine("						<th>Сумма площадей</th>");
	sb->AppendLine("						<th>Сумма площадей с проёмами</th>");
	sb->AppendLine("						<th>Сумма площадей без проёмов</th>");
	sb->AppendLine("						<th>Кол-во проёмов</th>");
	sb->AppendLine("						<th>Информация по проёму</th>");
	sb->AppendLine("					</tr>");
	sb->AppendLine("				</thead>");
	sb->AppendLine("				<tbody>");

	for each (MyDomain::Elements::AuditWallOpenings::AuditWallGroup^ auditWallGroup in resultReport->AuditResult->AuditWallGroups) {
		sb->AppendLine("					<tr>");
		sb->AppendLine("						<td>");
		sb->AppendLine("							<div class=\"data-row\">");
				

		for each (MyDomain::Elements::AuditWallOpenings::Scop^ scop in auditWallGroup->Scops) {
			sb->AppendLine("								<p>" + scop->name + " - " + scop->value + "</p>");
		}

		sb->AppendLine("							</div>");
		sb->AppendLine("						</td>");
		//sb->AppendLine("						<td><span class=\"data-row\">" + auditWallGroup->Name + "</span></td>");
		sb->AppendLine("						<td><span class=\"data-row\">" + auditWallGroup->TotalWalls + "</span></td>");
		sb->AppendLine("						<td><span class=\"data-row\">" + auditWallGroup->TotalArea.ToString("F3") + "</span></td>");
		sb->AppendLine("						<td><span class=\"data-row\">" + auditWallGroup->TotalAreaWallsWithOpenings.ToString("F3") + "</span></td>");
		sb->AppendLine("						<td><span class=\"data-row\">" + auditWallGroup->TotalAreaWallsWithoutOpenings.ToString("F3") + "</span></td>");
		sb->AppendLine("						<td><span class=\"data-row\">" + auditWallGroup->TotalOpenings + "</span></td>");
		sb->AppendLine("						<td class=\"opening-col\">");
		sb->AppendLine("						<details>");
		sb->AppendLine("						<summary class=\"opening-sum\">Проёмы</summary>");

		for each (MyDomain::Elements::AuditWallOpenings::AuditOpening^ opening in auditWallGroup->AuditOpenings) {
			sb->AppendLine("							<div class=\"opening\">");
			sb->AppendLine("								<p>Id: " + opening->Element->Id + "</p>");
			sb->AppendLine("								<p>Имя: " + opening->Element->Name + "</p>");
			sb->AppendLine("								<p>Категория: " + opening->Element->CategoryName + "</p>");
			sb->AppendLine("							</div>");

		}

		sb->AppendLine("						</details>");
		sb->AppendLine("						</td>");
		sb->AppendLine("					</tr>");

	}
	/*
	for each (KeyValuePair<String^, MyDomain::WallOpening::WallTypeInfo^> kvp in report->WallTypes) {
		sb->AppendLine("					<tr>");
		sb->AppendLine("						<td><span class=\"data-row\">" + kvp.Value->Name + "</span></td>");
		sb->AppendLine("						<td><span class=\"data-row\">" + kvp.Value->TotalWalls + "</span></td>");
		sb->AppendLine("						<td><span class=\"data-row\">" + kvp.Value->TotalArea.ToString("F3") + "</span></td>");
		sb->AppendLine("						<td><span class=\"data-row\">" + kvp.Value->TotalAreaWallsWithOpenings.ToString("F3") + "</span></td>");
		sb->AppendLine("						<td><span class=\"data-row\">" + kvp.Value->TotalAreaWallsWithoutOpenings.ToString("F3") + "</span></td>");
		sb->AppendLine("						<td><span class=\"data-row\">" + kvp.Value->TotalOpenings + "</span></td>");
		sb->AppendLine("						<td class=\"opening-col\">");
		sb->AppendLine("						<details>");
		sb->AppendLine("						<summary class=\"opening-sum\">Проёмы</summary>");

		for each (MyDomain::WallOpening::OpeningInfo^ openingInfo in kvp.Value->Openings) {
			sb->AppendLine("							<div class=\"opening\">");
			sb->AppendLine("								<p>Id: " + openingInfo->Id + "</p>");
			sb->AppendLine("								<p>Имя: " + openingInfo->Name + "</p>");
			sb->AppendLine("								<p>Категория: " + openingInfo->CategoryName + "</p>");
			sb->AppendLine("							</div>");
		}

		sb->AppendLine("						</details>");
		sb->AppendLine("						</td>");
		sb->AppendLine("					</tr>");
	}
	*/
	sb->AppendLine("				</tbody>");
	sb->AppendLine("			</table>");
	sb->AppendLine("		</details>");
	sb->AppendLine("	</section>");
	sb->AppendLine("	<section>");
	sb->AppendLine("		<details>");
	sb->AppendLine("		<summary><strong>Отчет по экземпляру</strong></summary>");
	sb->AppendLine("			<table>");
	sb->AppendLine("				<thead>");
	sb->AppendLine("					<tr>");
	sb->AppendLine("						<th>Id</th>");
	sb->AppendLine("						<th>Имя</th>");
	sb->AppendLine("						<th>Площадь</th>");
	sb->AppendLine("						<th>Кол-во проёмов</th>");
	sb->AppendLine("						<th>Информация по проёму</th>");
	sb->AppendLine("					</tr>");
	sb->AppendLine("				</thead>");
	sb->AppendLine("				<tbody>");

	for each (MyDomain::Elements::AuditWallOpenings::AuditWallElement^ wallElement in resultReport->AuditResult->AuditWallElements) {
		sb->AppendLine("					<tr>");
		sb->AppendLine("						<td><span class=\"data-row\">" + wallElement->WallElement->Id + "</span></td>");
		sb->AppendLine("						<td><span class=\"data-row\">" + wallElement->WallElement->Name + "</span></td>");
		sb->AppendLine("						<td><span class=\"data-row\">" + wallElement->WallElement->Area.ToString("F3") + "</span></td>");
		sb->AppendLine("						<td><span class=\"data-row\">" + wallElement->WallElement->CountOpenings + "</span></td>");
		sb->AppendLine("						<td class=\"opening-col\">");

		for each (MyDomain::Elements::AuditWallOpenings::AuditOpening^ opening in wallElement->AuditOpenings) {
			sb->AppendLine("							<div class=\"opening\">");
			sb->AppendLine("								<p>Id: " + opening->Element->Id + "</p>");
			sb->AppendLine("								<p>Имя: " + opening->Element->Name + "</p>");
			sb->AppendLine("								<p>Категория: " + opening->Element->CategoryName + "</p>");
			sb->AppendLine("							</div>");
		
		}

		sb->AppendLine("						</td>");
		sb->AppendLine("					</tr>");

	}
	/*
	for each (MyDomain::WallOpening::WallElementInfo^ wallElement in report->WallElemnts) {
		sb->AppendLine("					<tr>");
		sb->AppendLine("						<td><span class=\"data-row\">" + wallElement->Id + "</span></td>");
		sb->AppendLine("						<td><span class=\"data-row\">" + wallElement->Name + "</span></td>");
		sb->AppendLine("						<td><span class=\"data-row\">" + wallElement->Area.ToString("F3") + "</span></td>");
		sb->AppendLine("						<td><span class=\"data-row\">" + wallElement->CountOpenings + "</span></td>");
		sb->AppendLine("						<td class=\"opening-col\">");

		for each (MyDomain::WallOpening::OpeningInfo^ openingInfo in wallElement->Openings) {
			sb->AppendLine("							<div class=\"opening\">");
			sb->AppendLine("								<p>Id: " + openingInfo->Id + "</p>");
			sb->AppendLine("								<p>Имя: " + openingInfo->Name + "</p>");
			sb->AppendLine("								<p>Категория: " + openingInfo->CategoryName + "</p>");
			sb->AppendLine("							</div>");
		}

		sb->AppendLine("						</td>");
		sb->AppendLine("					</tr>");
	}
	*/
	sb->AppendLine("				</tbody>");
	sb->AppendLine("			</table>");
	sb->AppendLine("		</details>");
	sb->AppendLine("	</section>");

	sb->AppendLine("	</body>");
}

}//namespace ExportHtml