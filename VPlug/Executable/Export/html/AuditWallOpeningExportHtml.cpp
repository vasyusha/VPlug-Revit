#include "../../../Headers/Export/html/AuditWallOpeningExportHtml.h"

namespace ExportHtml {

String^ AuditWallOpeningExportHtml::BuildHtml(MyDomain::WallOpening::WallOpeningReport^ report) {
	if (report == nullptr)
		throw gcnew ArgumentNullException("report");

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
	sb->AppendLine("			vertical-aling: top;");
	sb->AppendLine("			border: 1px solid #bfb6c9;");
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

	AppendBody(sb, report);


	sb->AppendLine("</html>");
}

void AuditWallOpeningExportHtml::AppendBody(StringBuilder^ sb, MyDomain::WallOpening::WallOpeningReport^ report) {
	sb->AppendLine("<body>");
	sb->AppendLine("	<header>");
	sb->AppendLine("		<h1>VPlug - отчет кол-во проёмов в стенах</h1>");
	sb->AppendLine("		<div>");
	sb->AppendLine("			<p>Файл: <span>" + report->ProjectName + "</span></p>");
	sb->AppendLine("			<p>Дата: <span>" + report->DateTimeStr + "</span></p>");
	sb->AppendLine("		</div>");
	sb->AppendLine("	</header>");
	sb->AppendLine("	<hr>");
	sb->AppendLine("	<section>");
	sb->AppendLine("		<details>");
	sb->AppendLine("		<summary><strong>Отчет по типу</strong></summary>");
	sb->AppendLine("			<table>");
	sb->AppendLine("				<thead>");
	sb->AppendLine("					<tr>");
	sb->AppendLine("						<th>Имя типа</th>");
	sb->AppendLine("						<th>Кол-во элементов</th>");
	sb->AppendLine("						<th>Сумма площадей</th>");
	sb->AppendLine("						<th>Сумма площадей с проёмами</th>");
	sb->AppendLine("						<th>Сумма площадей без проёмов</th>");
	sb->AppendLine("						<th>Кол-во проёмов</th>");
	sb->AppendLine("						<th>Информация по проёму</th>");
	sb->AppendLine("					</tr>");
	sb->AppendLine("				</thead>");
	sb->AppendLine("				<tbody>");

	for each (KeyValuePair<String^, MyDomain::WallOpening::WallTypeInfo^> kvp in report->WallTypes) {
		sb->AppendLine("					<tr>");
		sb->AppendLine("						<td>" + kvp.Value->Name + "</td>");
		sb->AppendLine("						<td>" + kvp.Value->TotalWalls + "</td>");
		sb->AppendLine("						<td>" + kvp.Value->TotalArea.ToString("F3") + "</td>");
		sb->AppendLine("						<td>" + kvp.Value->TotalAreaWallsWithOpenings.ToString("F3") + "</td>");
		sb->AppendLine("						<td>" + kvp.Value->TotalAreaWallsWithoutOpenings.ToString("F3") + "</td>");
		sb->AppendLine("						<td>" + kvp.Value->TotalOpenings + "</td>");
		sb->AppendLine("						<td class=\"opening-col\">");

		for each (MyDomain::WallOpening::OpeningInfo^ openingInfo in kvp.Value->Openings) {
			sb->AppendLine("							<div class=\"opening\">");
			sb->AppendLine("								<p>Id: " + openingInfo->Id + "</p>");
			sb->AppendLine("								<p>Имя: " + openingInfo->Name + "</p>");
			sb->AppendLine("								<p>Категория: " + openingInfo->CategoryName + "</p>");
			sb->AppendLine("							</div>");
		}

		sb->AppendLine("						</td>");
		sb->AppendLine("					</tr>");
	}

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

	for each (MyDomain::WallOpening::WallElementInfo^ wallElement in report->WallElemnts) {
		sb->AppendLine("					<tr>");
		sb->AppendLine("						<td>" + wallElement->Id + "</td>");
		sb->AppendLine("						<td>" + wallElement->Name + "</td>");
		sb->AppendLine("						<td>" + wallElement->Area.ToString("F3") + "</td>");
		sb->AppendLine("						<td>" + wallElement->CountOpenings + "</td>");
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
	sb->AppendLine("				</tbody>");
	sb->AppendLine("			</table>");
	sb->AppendLine("		</details>");
	sb->AppendLine("	</section>");

	sb->AppendLine("	</body>");
}

}//namespace ExportHtml