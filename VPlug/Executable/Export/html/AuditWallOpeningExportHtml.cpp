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
	sb->AppendLine("<head>");
	sb->AppendLine("	<meta charset=\"utf-8\"/>");
	sb->AppendLine("	<title>VPlug—отчёт</title>");
	sb->AppendLine("	<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"/>");
	sb->AppendLine("	<style>");
	sb->AppendLine("		:root {");
	sb->AppendLine("			--bg: #0d1117;");
	sb->AppendLine("			--bg-elevated: #161b22;");
	sb->AppendLine("			--border-color: #30363d;");
	sb->AppendLine("			--text-main: #e6edf3;");
	sb->AppendLine("			--text-muted: #8b949e;");
	sb->AppendLine("			--accent: #2f81f7;");
	sb->AppendLine("			--accent-soft: rgba(47,129,247,0.15);");
	sb->AppendLine("			--header-bg: #25292e;");
	sb->AppendLine("			--danger: #f85149;");
	sb->AppendLine("		}");
	sb->AppendLine("		* {");
	sb->AppendLine("			box-sizing: border-box;");
	sb->AppendLine("		}");
	sb->AppendLine("		body {");
	sb->AppendLine("			margin: 0;");
	sb->AppendLine("			padding: 0;");
	sb->AppendLine("			padding-top: 64px;");
	sb->AppendLine("			font-family: system-ui, -apple-system, BlinkMacSystemFont, \"Segoe UI\", Arial, sans-serif;");
	sb->AppendLine("			background-color: var(--bg);");
	sb->AppendLine("			color: var(--text-main);");
	sb->AppendLine("		}");
	sb->AppendLine("		header {");
	sb->AppendLine("			position: fixed;");
	sb->AppendLine("			top: 0;");
	sb->AppendLine("			left: 0;");
	sb->AppendLine("			right: 0;");
	sb->AppendLine("			height: 64px;");
	sb->AppendLine("			background: var(--header-bg);");
	sb->AppendLine("			display: flex;");
	sb->AppendLine("			align-items: center;");
	sb->AppendLine("			justify-content: center;");
	sb->AppendLine("			box-shadow: 0 2px 8px rgba(0,0,0,0.4);");
	sb->AppendLine("			z-index: 10;");
	sb->AppendLine("		}");
	sb->AppendLine("		.brand {");
	sb->AppendLine("			font-size: 20px;");
	sb->AppendLine("			font-weight: 600;");
	sb->AppendLine("			letter-spacing: 0.05em;");
	sb->AppendLine("		}");
	sb->AppendLine("		.brand span {");
	sb->AppendLine("			color: var(--accent);");
	sb->AppendLine("		}");
	sb->AppendLine("		.brand a:hover {");
	sb->AppendLine("			text-decoration: none;");
	sb->AppendLine("		}");
	sb->AppendLine("		.brand a {");
	sb->AppendLine("			color: var(--text-main);");
	sb->AppendLine("			text-decoration: none;");
	sb->AppendLine("		}");
	sb->AppendLine("		.brand a:visited {");
	sb->AppendLine("			color: var(--text-main);");
	sb->AppendLine("		}");
	sb->AppendLine("		.page {");
	sb->AppendLine("			max-width: 1300px;");
	sb->AppendLine("			margin: 0 auto;");
	sb->AppendLine("			padding: 20px 16px 40px;");
	sb->AppendLine("		}");
	sb->AppendLine("		.report-header {");
	sb->AppendLine("			display: flex;");
	sb->AppendLine("			flex-wrap: wrap;");
	sb->AppendLine("			gap: 12px;");
	sb->AppendLine("			align-items: center;");
	sb->AppendLine("			justify-content: space-between;");
	sb->AppendLine("			margin-bottom: 20px;");
	sb->AppendLine("		}");
	sb->AppendLine("		.report-title {");
	sb->AppendLine("			font-size: 22px;");
	sb->AppendLine("			font-weight: 600;");
	sb->AppendLine("		}");
	sb->AppendLine("		.report-tag {");
	sb->AppendLine("			display: inline-flex;");
	sb->AppendLine("			align-items: center;");
	sb->AppendLine("			gap: 6px;");
	sb->AppendLine("			padding: 4px 10px;");
	sb->AppendLine("			border-radius: 999px;");
	sb->AppendLine("			border: 1px solid var(--border-color);");
	sb->AppendLine("			background: var(--bg-elevated);");
	sb->AppendLine("			font-size: 13px;");
	sb->AppendLine("		}");
	sb->AppendLine("		.dot {");
	sb->AppendLine("			width: 8px;");
	sb->AppendLine("			height: 8px;");
	sb->AppendLine("			border-radius: 50%;");
	sb->AppendLine("			background: var(--accent);");
	sb->AppendLine("		}");
	sb->AppendLine("		.meta {");
	sb->AppendLine("			display: flex;");
	sb->AppendLine("			flex-wrap: wrap;");
	sb->AppendLine("			gap: 12px;");
	sb->AppendLine("			font-size: 13px;");
	sb->AppendLine("			color: var(--text-muted);");
	sb->AppendLine("		}");
	sb->AppendLine("		.meta-item strong {");
	sb->AppendLine("			color: var(--text-main);");
	sb->AppendLine("		}");
	sb->AppendLine("		.card {");
	sb->AppendLine("			background: var(--bg-elevated);");
	sb->AppendLine("			border-radius: 10px;");
	sb->AppendLine("			border: 1px solid var(--border-color);");
	sb->AppendLine("			padding: 16px 16px 12px;");
	sb->AppendLine("			margin-bottom: 16px;");
	sb->AppendLine("		}");
	sb->AppendLine("		.card h2 {");
	sb->AppendLine("			margin: 0 0 10px;");
	sb->AppendLine("			font-size: 16px;");
	sb->AppendLine("			font-weight: 600;");
	sb->AppendLine("		}");
	sb->AppendLine("		.card p {");
	sb->AppendLine("			margin: 4px 0;");
	sb->AppendLine("			font-size: 14px;");
	sb->AppendLine("			color: var(--text-muted);");
	sb->AppendLine("		}");
	sb->AppendLine("		.data-table-wrapper {");
	sb->AppendLine("			margin-top: 10px;");
	sb->AppendLine("			overflow-x: visible;");
	sb->AppendLine("		}");
	sb->AppendLine("		table.data-table {");
	sb->AppendLine("			width: 100%;");
	sb->AppendLine("			border-collapse: collapse;");
	sb->AppendLine("			font-size: 14px;");
	sb->AppendLine("			min-width: 420px;");
	sb->AppendLine("		}");
	sb->AppendLine("		.data-table thead {");
	sb->AppendLine("			background: var(--accent-soft);");
	sb->AppendLine("		}");
	sb->AppendLine("		.data-table th,");
	sb->AppendLine("		.data-table td {");
	sb->AppendLine("			min-width: 80px;");
	sb->AppendLine("			padding: 8px 10px;");
	sb->AppendLine("			border-bottom: 1px solid var(--border-color);");
	sb->AppendLine("			text-align: left;");
	sb->AppendLine("			white-space: nowrap; /*Запрет переноса слов*/");
	sb->AppendLine("			/*white-space: normal;*//* разрешить перенос строк*/");
	sb->AppendLine("			/*word-break: break-word;*//* ломать длинные слова */");
	sb->AppendLine("			vertical-align: top;");
	sb->AppendLine("		}");
	sb->AppendLine("		.data-table th {");
	sb->AppendLine("			font-weight: 500;");
	sb->AppendLine("		}");
	sb->AppendLine("		.data-table tbody tr:nth-child(even) {");
	sb->AppendLine("			background: rgba(255,255,255,0.02);");
	sb->AppendLine("		}");
	sb->AppendLine("		.data-table tbody tr:hover {");
	sb->AppendLine("			background: rgba(255,255,255,0.04);");
	sb->AppendLine("		}");
	sb->AppendLine("		footer {");
	sb->AppendLine("			margin-top: 24px;");
	sb->AppendLine("			font-size: 12px;");
	sb->AppendLine("			color: var(--text-muted);");
	sb->AppendLine("			text-align: right;");
	sb->AppendLine("		}");
	sb->AppendLine("");
	sb->AppendLine("		span.data-row, div.data-row {");
	sb->AppendLine("			position: sticky;");
	sb->AppendLine("			top: 90px;");
	sb->AppendLine("			z-index: 2;");
	sb->AppendLine("		}");
	sb->AppendLine("		summary.opening-sum {");
	sb->AppendLine("			font-size: 16px;");
	sb->AppendLine("		}");
	sb->AppendLine("		td.opening-col {");
	sb->AppendLine("			max-width: 200px;");
	sb->AppendLine("			white-space: normal;");
	sb->AppendLine("			word-break: break-word;");
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
	sb->AppendLine("		.opening-col,");
	sb->AppendLine("		.opening-col p,");
	sb->AppendLine("		.data-row,");
	sb->AppendLine("		.data-row p {");
	sb->AppendLine("			white-space: normal;");
	sb->AppendLine("			word-break: break-word;");
	sb->AppendLine("		}");
	sb->AppendLine("	</style>");
	sb->AppendLine("</head>");

	AppendBody(sb, resultReport);

	sb->AppendLine("</html>");
}

void AuditWallOpeningExportHtml::AppendBody(StringBuilder^ sb, MyDomain::AuditWallOpeningsReport::ResultReport^ resultReport) {
	sb->AppendLine("<body>");

	sb->AppendLine("<header>");
	sb->AppendLine("	<div class=\"brand\"><a href=\"https://github.com/vasyusha/VPlug-Revit\"><span>V</span>Plug</a></div>");
	sb->AppendLine("</header>");
	sb->AppendLine("<main class=\"page\">");
	sb->AppendLine("	<section class=\"report-header\">");
	sb->AppendLine("		<div>");
	sb->AppendLine("			<div class=\"report-title\">");
	sb->AppendLine("				Отчёт: количество проёмов в стенах");
	sb->AppendLine("			</div>");
	sb->AppendLine("			<div class=\"report-tag\">");
	sb->AppendLine("				<span class=\"dot\"></span>");
	sb->AppendLine("					Аналитический отчёт");
	sb->AppendLine("			</div>");
	sb->AppendLine("		</div>");
	sb->AppendLine("		<div class=\"meta\">");
	sb->AppendLine("			<div class=\"meta-item\">");
	sb->AppendLine("				Модель: <strong>" + resultReport->ProjectName + ".rvt</strong>");
	sb->AppendLine("			</div>");
	sb->AppendLine("			<div class=\"meta-item\">");
	sb->AppendLine("				Дата отчета: <strong>" + resultReport->DateTimeStr + "</strong>");
	sb->AppendLine("			</div>");
	sb->AppendLine("			<div class=\"meta-item\">");
	sb->AppendLine("				Плагин: <strong>VPlug</strong>");
	sb->AppendLine("			</div>");
	sb->AppendLine("		</div>");
	sb->AppendLine("	</section>");
	sb->AppendLine("	<section class=\"card\">");
	sb->AppendLine("		<h2>Краткое резюме</h2>");
	sb->AppendLine("		<p>Обратобано фильтров - " + resultReport->AuditResult->AuditWallGroups->Count.ToString() + "</p>");
	sb->AppendLine("		<p>Обработано элементов - " + resultReport->AuditResult->AuditWallElements->Count.ToString() + "</p>");
	sb->AppendLine("	</section>");
	sb->AppendLine("	<section class=\"card\">");
	sb->AppendLine("		<h2>Сводка по фильтру</h2>");
	sb->AppendLine("		<div class=\"data-table-wrapper\">");
	sb->AppendLine("			<table class=\"data-table\">");
	sb->AppendLine("				<thead>");
	sb->AppendLine("					<tr>");
	sb->AppendLine("						<th>Фильтер</th>");
	sb->AppendLine("						<th>Кол-во элементов</th>");
	sb->AppendLine("						<th>Сумма площадей</th>");
	sb->AppendLine("						<th>Сумма площадей без проёмов</th>");
	sb->AppendLine("						<th>Сумма площадей с проёмами</th>");
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
			sb->AppendLine("							<p>" + scop->name + " - " + scop->value + "</p>");
		}
		sb->AppendLine("							</div>");

		sb->AppendLine("						</td>");
		sb->AppendLine("						<td><span class=\"data-row\">" + auditWallGroup->TotalWalls + "</span></td>");
		sb->AppendLine("						<td><span class=\"data-row\">" + auditWallGroup->TotalArea.ToString("F3") + "</span></td>");
		sb->AppendLine("						<td><span class=\"data-row\">" + auditWallGroup->TotalAreaWallsWithOpenings.ToString("F3") + "</span></td>");
		sb->AppendLine("						<td><span class=\"data-row\">" + auditWallGroup->TotalAreaWallsWithoutOpenings.ToString("F3") + "</span></td>");
		sb->AppendLine("						<td><span class=\"data-row\">" + auditWallGroup->TotalOpenings + "</span></td>");
		
		if (auditWallGroup->AuditOpenings != nullptr && auditWallGroup->AuditOpenings->Count > 0) {
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

		} else {
			sb->AppendLine("						<td><span class=\"data-row\">-</span></td>");
		}

		sb->AppendLine("					</tr>");
	}

	sb->AppendLine("				</tbody>");
	sb->AppendLine("			</table>");
	sb->AppendLine("		</div>");
	sb->AppendLine("	</section>");
	sb->AppendLine("	<section class=\"card\">");
	sb->AppendLine("		<details>");
	sb->AppendLine("			<summary>");
	sb->AppendLine("				<strong>Сводка по элементу</strong>");
	sb->AppendLine("			</summary>");
	sb->AppendLine("		<div class=\"data-table-wrapper\">");
	sb->AppendLine("			<table class=\"data-table\">");
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

		if (wallElement->AuditOpenings != nullptr && wallElement->AuditOpenings->Count > 0) {
			sb->AppendLine("						<td class=\"opening-col\">");
			sb->AppendLine("						<details>");
			sb->AppendLine("						<summary class=\"opening-sum\">Проёмы</summary>");

			for each (MyDomain::Elements::AuditWallOpenings::AuditOpening^ opening in wallElement->AuditOpenings) {
				sb->AppendLine("							<div class=\"opening\">");
				sb->AppendLine("								<p>Id: " + opening->Element->Id + "</p>");
				sb->AppendLine("								<p>Имя: " + opening->Element->Name + "</p>");
				sb->AppendLine("								<p>Категория: " + opening->Element->CategoryName + "</p>");
				sb->AppendLine("							</div>");
			}

			sb->AppendLine("						</details>");
			sb->AppendLine("						</td>");

		} else {
			sb->AppendLine("						<td><span class=\"data-row\">-</span></td>");
		}
		sb->AppendLine("					</tr>");
	}
		
	sb->AppendLine("				</tbody>");
	sb->AppendLine("			</table>");
	sb->AppendLine("		</div>");
	sb->AppendLine("		</details>");
	sb->AppendLine("	</section>");
	sb->AppendLine("	<section class=\"card\">");
	sb->AppendLine("		<h2>Примечания</h2>");
	sb->AppendLine("		<p>всяко всяко</p>");
	sb->AppendLine("	</section>");
	sb->AppendLine("	<footer>");
	sb->AppendLine("		Отчёт сформирован автоматически плагином VPlug.");
	sb->AppendLine("	</footer>");
	sb->AppendLine("</main>");
	sb->AppendLine("</body>");
}

}//namespace ExportHtml