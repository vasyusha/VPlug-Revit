#include "../../../Headers/Export/html/AuditParameterExportHtml.h"

namespace ExportHtml {

String^ AuditParameterExportHtml::BuildHtml(MyDomain::AuditParameterReport::ResultReport^ reportResult) {
	if (reportResult == nullptr)
		throw gcnew ArgumentNullException("resultReport == nullprt");

	StringBuilder^ sb = gcnew StringBuilder();

	AppendHeader(sb, reportResult);

	return sb->ToString();
}

void AuditParameterExportHtml::SaveHtmlToFile(MyDomain::AuditParameterReport::ResultReport^ reportResult, String^ path) {
	String^ html = BuildHtml(reportResult);
	StreamWriter^ w = gcnew StreamWriter(path, false, System::Text::Encoding::UTF8);
	w->Write(html);
	w->Close();
}

void AuditParameterExportHtml::AppendHeader(StringBuilder^ sb, MyDomain::AuditParameterReport::ResultReport^ reportResult) {

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
	sb->AppendLine("");
	sb->AppendLine("			--green: #97cc64;");
	sb->AppendLine("			--red: #fb5a3e;");
	sb->AppendLine("			--border:#e6e8ee;");
	sb->AppendLine("			--ok-bg:#e8f6ec;");
	sb->AppendLine("			--ok-border:#b8e3c6;");
	sb->AppendLine("			--ok-text:#166534;");
	sb->AppendLine("			--bad-bg:#ffe9e9;");
	sb->AppendLine("			--bad-border:#ffbcbc;");
	sb->AppendLine("			--bad-text:#8a1420;");
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
	sb->AppendLine("			/*white-space: nowrap;*/ /*Запрет переноса слов*/");
	sb->AppendLine("			white-space: normal;/* разрешить перенос строк*/");
	sb->AppendLine("			word-break: break-word;/* ломать длинные слова */");
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
	sb->AppendLine("		td.name {");
	sb->AppendLine("			min-width: 250px;");
	sb->AppendLine("		}");
	sb->AppendLine("		.pass {");
	sb->AppendLine("			background-color: var(--ok-bg);");
	sb->AppendLine("		}");
	sb->AppendLine("		.fail {");
	sb->AppendLine("			background-color: var(--bad-bg);");
	sb->AppendLine("		}");
	sb->AppendLine("		.container {");
	sb->AppendLine("			width: 100%;");
	sb->AppendLine("			background-color: #ddd;");
	sb->AppendLine("			border-radius: 5px;");
	sb->AppendLine("		}");
	sb->AppendLine("		.percent {");
	sb->AppendLine("			text-align: left;");
	sb->AppendLine("			padding-top: 5px;");
	sb->AppendLine("			padding-left: 5px;");
	sb->AppendLine("			padding-bottom: 5px;");
	sb->AppendLine("			color: white;");
	sb->AppendLine("			border-radius: 5px;");
	sb->AppendLine("			white-space: nowrap;");
	sb->AppendLine("		}");
	sb->AppendLine("		span.item {");
	sb->AppendLine("			padding: 5px;");
	sb->AppendLine("			border-radius: 5px;");
	sb->AppendLine("			margin-right: 5px;");
	sb->AppendLine("			border: 1px solid #eee;");
	sb->AppendLine("		}");
	sb->AppendLine("		span.item.pass, span.item.fail {");
	sb->AppendLine("			color: #FFF;");
	sb->AppendLine("			font-weight: bold;");
	sb->AppendLine("			border: 0px;");
	sb->AppendLine("		}");
	sb->AppendLine("		span.item.pass {");
	sb->AppendLine("			background-color: var(--green);");
	sb->AppendLine("		}");
	sb->AppendLine("		span.item.fail {");
	sb->AppendLine("			background-color: var(--red);");
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
	sb->AppendLine("		}");
	sb->AppendLine("		div.percent.pass {");
	sb->AppendLine("			background: var(--green);");
	sb->AppendLine("		}");
	sb->AppendLine("		div.percent.fail {");
	sb->AppendLine("			background: var(--red);");
	sb->AppendLine("		}");
	sb->AppendLine("		.param {");
	sb->AppendLine("			display:inline-block;");
	sb->AppendLine("			padding: 6px 10px;");
	sb->AppendLine("			border-radius: 8px;");
	sb->AppendLine("			border: 1px dashed var(--border);");
	sb->AppendLine("			background: #fff;");
	sb->AppendLine("			font-size: 12px;");
	sb->AppendLine("			margin: 4px 6px 0 0;");
	sb->AppendLine("		}");
	sb->AppendLine("		.param.pass {");
	sb->AppendLine("			background: var(--ok-bg);");
	sb->AppendLine("			border-color: var(--ok-border);");
	sb->AppendLine("			color: var(--ok-text);");
	sb->AppendLine("			font-weight: 600;");
	sb->AppendLine("		}");
	sb->AppendLine("		.param.fail {");
	sb->AppendLine("			background: var(--bad-bg);");
	sb->AppendLine("			border-color: var(--bad-border);");
	sb->AppendLine("			color: var(--bad-text);");
	sb->AppendLine("		}");
	sb->AppendLine("	</style>");

	AppendBody(sb, reportResult);
}

void AuditParameterExportHtml::AppendBody(StringBuilder^ sb, MyDomain::AuditParameterReport::ResultReport^ resultReport) { 

	sb->AppendLine("<body>");
	sb->AppendLine("<header>");
	sb->AppendLine("	<div class=\"brand\"><a href=\"https://github.com/vasyusha/VPlug-Revit\"><span>V</span>Plug</a></div>");
	sb->AppendLine("</header>");
	sb->AppendLine("<main class=\"page\">");
	sb->AppendLine("	<section class=\"report-header\">");
	sb->AppendLine("		<div>");
	sb->AppendLine("			<div class=\"report-title\">");
	sb->AppendLine("				Отчёт: заполнение параметров");
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
	sb->AppendLine("		<div class=\"container\">");

	String^ passOrFailed = resultReport->Result->Pass == true ? "pass" : "fail";

	sb->AppendLine("			<div class=\"percent " + passOrFailed + "\" style=\"width: " + resultReport->Result->Percent + "%;\">" + resultReport->Result->Percent + "%</div>");
	sb->AppendLine("		</div>");
	sb->AppendLine("		</br>");
	sb->AppendLine("		<p>");

	String^ RuPassOrFailed = resultReport->Result->Pass == true ? "Успех" : "Ошибки";

	sb->AppendLine("			<span class=\"item " + passOrFailed + "\">" + RuPassOrFailed + "</span>");
	sb->AppendLine("			<span class=\"item\">");
	sb->AppendLine("				Спецификации пройдены: <strong>" + resultReport->Result->PassGroups + "</strong>/<strong>" + resultReport->Result->TotalGroups + "</strong>");
	sb->AppendLine("			</span>");
	sb->AppendLine("			<span class=\"item\">");
	sb->AppendLine("				Требования приняты: <strong>" + resultReport->Result->ReqElementPass + "</strong>/<strong>" + resultReport->Result->ReqElementTotal + "</strong>");
	sb->AppendLine("			</span>");
	sb->AppendLine("			<span class=\"item\">");
	sb->AppendLine("				Проверки пройдены: <strong>" + resultReport->Result->ReqParamPass + "</strong>/<strong>" + resultReport->Result->ReqParamTotal + "</strong>");
	sb->AppendLine("			</span>");
	sb->AppendLine("		</p>");
	sb->AppendLine("	</section>");

	AppendSection(sb, resultReport);


	sb->AppendLine("	<section class=\"card\">");
	sb->AppendLine("		<h2>Примечания</h2>");
	sb->AppendLine("		<p>всяко всяко</p>");
	sb->AppendLine("	</section>");
	sb->AppendLine("	<footer>");
	sb->AppendLine("		Отчёт сформирован автоматически плагином VPlug.");
	sb->AppendLine("	</footer>");
	sb->AppendLine("</main>");

	sb->AppendLine("</body>");
	sb->AppendLine("</html>");
}

void AuditParameterExportHtml::AppendSection(StringBuilder^ sb, MyDomain::AuditParameterReport::ResultReport^ resultRepor) {
	int numCategory = 1;

	for each (MyDomain::Elements::AuditParameters::AuditGroup^ groupReport in resultRepor->Result->Groups) {

		sb->AppendLine("	<section class=\"card\" style=\"clear: both; overflow: hidden;\">");
		sb->AppendLine("		<div class=\"info\">");
		sb->AppendLine("			<h2>" + numCategory + ". " + groupReport->Name + "</h2>");
		sb->AppendLine("			<div class=\"container\">");

		String^ passOrFailed = groupReport->Pass == true ? "pass" : "fail";

		if (groupReport->Elements->Count == 0) {

			sb->AppendLine("				Отсутствует");
			sb->AppendLine("			</div>");
			sb->AppendLine("			<br>");
			sb->AppendLine("			<p><span class=\"item\">Отсутствует</span></p>");
			sb->AppendLine("			<br>");

		} else {

			sb->AppendLine("				<div class=\"percent " + passOrFailed + "\" style=\"width: " + groupReport->Percent + "%;\">" + groupReport->Percent + "%</div>");
			sb->AppendLine("			</div>");

			String^ RuPassOrFailed = groupReport->Pass == true ? "Успех" : "Ошибки";

			sb->AppendLine("			<br>");
			sb->AppendLine("			<p><span class=\"item " + passOrFailed + "\">" + RuPassOrFailed + "</span></p>");
			sb->AppendLine("			<br>");

		}

		sb->AppendLine("			<p><span class=\"item\">Элементы прошли: <strong>" + groupReport->PassElements + "</strong>/<strong>" + groupReport->TotalElements + "</strong></span></p>");
		sb->AppendLine("			<br>");
		sb->AppendLine("			<p><span class=\"item\">Проверки пройдены: <strong>" + groupReport->PassParams + "</strong>/<strong>" + groupReport->TotalParams + "</strong></span></p>");
		sb->AppendLine("			<br>");
		sb->AppendLine("		</div>");	
		sb->AppendLine("		<div class=\"results\">");
		sb->AppendLine("			<p><strong>Применимо</strong></p>");
		sb->AppendLine("			<ul>");
		sb->AppendLine("				<li>" + groupReport->Name + "</li>");	
		sb->AppendLine("			</ul>");
		sb->AppendLine("			<p><strong>Требования</strong></p>");
		sb->AppendLine("			<p><span>Заполнение параметров</span>");
		sb->AppendLine("			<ul>");
	
		for each (String^ p in groupReport->CheckedParameters) {
			sb->AppendLine("				<li>" + p + "</li>");
		}

		sb->AppendLine("			</ul>");
		sb->AppendLine("			<hr>");
		sb->AppendLine("			<p><span>Данные по элементам</span></p>");
		sb->AppendLine("				<details>");
		sb->AppendLine("					<summary>Таблица всех элементов по группе</summary>");
		sb->AppendLine("				<table class=\"data-table\">");
		sb->AppendLine("					<thead>");
		sb->AppendLine("						<tr>");
		sb->AppendLine("							<th>Id</th>");
		sb->AppendLine("							<th>Имя</th>");
		sb->AppendLine("							<th>Параметры</th>");
		sb->AppendLine("						</tr>");
		sb->AppendLine("					</thead>");
		sb->AppendLine("					<tbody>");

		for each (MyDomain::Elements::AuditParameters::AuditElement^ auditElement in groupReport->Elements) {
			String^ passOrFailedElement = auditElement->Pass == true ? "ok" : "bad";

			sb->AppendLine("						<tr data-row=\"" + passOrFailedElement + "\">");
			sb->AppendLine("							<td>" + auditElement->Element->Id + "</td>");
			sb->AppendLine("							<td>" + auditElement->Element->Name + "</td>");
			sb->AppendLine("							<td>");

			for each (MyDomain::Parameters::Parameter^ parameter in auditElement->Element->Parameters) {
				String^ passOrFailedParam = parameter->Filled == true ? "pass" : "fail";

				sb->AppendLine("								<span class=\"param " + passOrFailedParam + "\">" + parameter->Name + "</span>");

			}

			sb->AppendLine("							</td>");
			sb->AppendLine("						</tr>");
		}

		sb->AppendLine("					</tbody>");
		sb->AppendLine("				</table>");
		sb->AppendLine("				</details>");
		sb->AppendLine("			<hr>");
	
		sb->AppendLine("	</section>");
		++numCategory;	
	}
}

}// namespace ExportHtml