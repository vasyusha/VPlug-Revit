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
	sb->AppendLine("<html lang=\"ru\">");
	sb->AppendLine("<head>");
	sb->AppendLine("	<meta charset=\"utf-8\"/>");
	sb->AppendLine("	<title>Отче: заполнение параметров</title>");
	sb->AppendLine("	<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"/>");
	sb->AppendLine("	<style>");
	sb->AppendLine("		:root {");
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
	sb->AppendLine("		body { font-family: 'Arial', sans-serif; padding: 10px 40px; }");
	sb->AppendLine("		.pass { background-color: var(--ok-bg); }");
	sb->AppendLine("		.fail { background-color: var(--bad-bg); }");
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
	sb->AppendLine("			border-radius:");
	sb->AppendLine("			5px; white-space: nowrap;");
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
	sb->AppendLine("		span.item.fail{");
	sb->AppendLine("			background-color: var(--red);");
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
	sb->AppendLine("		div.percent.pass {");
	sb->AppendLine("			background:var(--green);");
	sb->AppendLine("		}");
	sb->AppendLine("		div.percent.fail{");
	sb->AppendLine("			background:var(--red);");
	sb->AppendLine("		}");
	sb->AppendLine("		table {");
	sb->AppendLine("			width:100%;");
	sb->AppendLine("			border-collapse:separate;");
	sb->AppendLine("			border-spacing:0;");
	sb->AppendLine("		}");
	sb->AppendLine("		thead th {");
	sb->AppendLine("			position:sticky; top:0; z-index:1;");
	sb->AppendLine("			font-weight:700; text-align:left; padding:10px 12px; white-space:nowrap;");
	sb->AppendLine("			border-bottom:1px solid var(--border);");
	sb->AppendLine("		}");
	sb->AppendLine("		tbody td {");
	sb->AppendLine("			padding:10px 12px; vertical-align:top; border-bottom:1px solid var(--border);");
	sb->AppendLine("		}");
	sb->AppendLine("		tbody tr[data-row=\"ok\"]{background:var(--ok-bg); }");
	sb->AppendLine("		tbody tr[data-row=\"bad\"]{background:var(--bad-bg);}");
	sb->AppendLine("		.param {");
	sb->AppendLine("			display:inline-block; padding:6px 10px; border-radius:8px; border:1px dashed var(--border);");
	sb->AppendLine("			background:#fff; font-size:12px; margin:4px 6px 0 0;");
	sb->AppendLine("		}");
	sb->AppendLine("		.param.pass {");
	sb->AppendLine("			background:var(--ok-bg); border-color:var(--ok-border); color:var(--ok-text);");
	sb->AppendLine("			font-weight:600;");
	sb->AppendLine("		}");
	sb->AppendLine("		.param.fail {");
	sb->AppendLine("			background:var(--bad-bg); border-color:var(--bad-border); color:var(--bad-text);");
	sb->AppendLine("		}");
	sb->AppendLine("	</style>");
	sb->AppendLine("</head>");
	
	AppendBody(sb, reportResult);
}

void AuditParameterExportHtml::AppendBody(StringBuilder^ sb, MyDomain::AuditParameterReport::ResultReport^ resultReport) { 
	sb->AppendLine("<body>");
	sb->AppendLine("	<header>");
	sb->AppendLine("		<h1>VPlug - отчет по параметрам</h1>");
	sb->AppendLine("		<div>");
	sb->AppendLine("			<p>Файл:<span>" + resultReport->ProjectName + "</span></p>");
	sb->AppendLine("			<p>Дата:<span>" + resultReport->DateTimeStr+ "</span></p>");
	sb->AppendLine("		</div>");
	sb->AppendLine("	</header>");
	sb->AppendLine("	<hr>");
	sb->AppendLine("	<h2>Краткое содержание</h2>");
	sb->AppendLine("	<div class=\"container\">");

	String^ passOrFailed = resultReport->Result->Pass == true ? "pass" : "fail";

	sb->AppendLine("		<div class=\"percent " + passOrFailed + "\" style=\"width: " + resultReport->Result->Percent + "%;\">" + resultReport->Result->Percent + "%</div>");
	sb->AppendLine("	</div>");
	sb->AppendLine("	<p>");

	String^ RuPassOrFailed = resultReport->Result->Pass == true ? "Успех" : "Ошибки";

	sb->AppendLine("		<span class=\"item " + passOrFailed + "\">" + RuPassOrFailed + "</span>");
	sb->AppendLine("		<span class=\"item\">");
	sb->AppendLine("			Спецификации пройдены: <strong>" + resultReport->Result->PassGroups + "</strong>/<strong>" + resultReport->Result->TotalGroups + "</strong>");
	sb->AppendLine("		</span>");
	sb->AppendLine("		<span class=\"item\">");
	sb->AppendLine("			Требования приняты: <strong>" + resultReport->Result->ReqElementPass + "</strong>/<strong>" + resultReport->Result->ReqElementTotal + "</strong>");
	sb->AppendLine("		</span>");
	sb->AppendLine("		<span class=\"item\">");
	sb->AppendLine("			Проверки пройдены: <strong>" + resultReport->Result->ReqParamPass + "</strong>/<strong>" + resultReport->Result->ReqParamTotal + "</strong>");
	sb->AppendLine("		</span>");
	sb->AppendLine("	</p>");
	sb->AppendLine("	<hr>");

	AppendSection(sb, resultReport);

	sb->AppendLine("</body>");
	sb->AppendLine("</html>");
}

void AuditParameterExportHtml::AppendSection(StringBuilder^ sb, MyDomain::AuditParameterReport::ResultReport^ resultRepor) {
	int numCategory = 1;
	for each (MyDomain::Elements::AuditParameters::AuditGroup^ groupReport in resultRepor->Result->Groups) {
		sb->AppendLine("	<section style=\"clear: both; overflow: hidden; \">");
		sb->AppendLine("		<div class=\"info\">");
		sb->AppendLine("			<h2>" + numCategory + ". " + groupReport->Name + "</h2>");	
		sb->AppendLine("			<div class=\"container\">");

		String^ passOrFailed = groupReport->Pass == true ? "pass" : "fail";
		if (groupReport->Elements->Count == 0) {
			sb->AppendLine("				<div>Отсутствует</div>");
			sb->AppendLine("			</div>");
			sb->AppendLine("			<p><span class=\"item\">Отсутствует</span></p>");
		} else {
			//String^ passOrFailed = cr->Pass == true ? "pass" : "fail";

			sb->AppendLine("				<div class=\"percent " + passOrFailed + "\" style=\"width: " + groupReport->Percent + "%;\">" + groupReport->Percent + "%</div>");
			sb->AppendLine("			</div>");

			String^ RuPassOrFailed = groupReport->Pass == true ? "Успех" : "Ошибки";
			sb->AppendLine("			<p><span class=\"item " + passOrFailed + "\">" + RuPassOrFailed + "</span></p>");
		}

		sb->AppendLine("			<p><span class=\"item\">Элементы прошли<strong>" + groupReport->PassElements + "</strong>/<strong>" + groupReport->TotalElements + "</strong></span></p>");
		sb->AppendLine("			<p><span class=\"item\">Проверки пройдены <strong>" + groupReport->PassParams + "</strong>/<strong>" + groupReport->TotalParams + "</strong></span></p>");
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
		sb->AppendLine("				<table class=\"" + passOrFailed + "\">");
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
			//String^ passOrFailedElement = r->Pass == true ? "pass" : "fail";
			//sb->AppendLine("						<tr class=\"" + passOrFailedElement + "\">");
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
		
		//sb->AppendLine("			p><span>Данные по параметрам</span></p>");
		//sb->AppendLine("			<ol>");
		//sb->AppendLine("				<li>");
		//sb->AppendLine("					<details>");

		//sb->AppendLine("					</details>");
		//sb->AppendLine("				</li>");
		//sb->AppendLine("			</ol>");
		
		sb->AppendLine("	</section>");
		++numCategory;	
	}
}



}// namespace ExportHtml