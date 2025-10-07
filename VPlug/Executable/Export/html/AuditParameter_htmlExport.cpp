#include "..\..\..\Headers\Export\html\AuditParameter_htmlExport.h"

Export::AuditParameterHtmlExport::AuditParameterHtmlExport(String^ path) : path_(path) {

};

void Export::AuditParameterHtmlExport::CompileFile(Dictionary<Tuple<String^, String^>^, List<Elements::BaseElement^>^>^ data) {

	StreamWriter^ output = gcnew StreamWriter(path_);
	output->Write(
		"<!doctype html>"
		"\r\n<head>"
		"\r\n\t<meta charset=\"utf - 8\" />"
		"\r\n\t\<title>Отчет</title>"
		"\r\n\t<style>"
		"\r\n\t\tbody {"
		"\r\n\t\t\tbackground-color: #CEAC73;"
		"\r\n\t\t}"
		"\r\n"
		"\r\n\t\ttable {"
		"\r\n\t\t\twidth: 100%;"
		"\r\n\t\t\tborder-collapse: collapse;"
		"\r\n\t\t\tborder: 2px solid #BF7242;"
		"\r\n\t\t\tfont-family: sans-serif;"
		"\r\n\t\t\tfont-size: 0.8rem;"
		"\r\n\t\t\tletter-spacing: 1px;"
		"\r\n\t\t}"
		"\r\n"
		"\r\n\t\tthead {"
		"\r\n\t\t\tbackground-color: #BF9042;"
		"\r\n\t\t}"
		"\r\n"
		"\r\n\t\tth, td {"
		"\r\n\t\t\tpadding: 12px 15px;"
		"\r\n\t\t\tborder: 1px solid #BF7242;"
		"\r\n\t\t\ttext-align: left;"
		"\r\n\t\t}"
		"\r\n"
		"\r\n\t\t#data {"
		"\r\n\t\t\tbackground-color: #CEAC73;"
		"\r\n\t\t}"
		"\r\n"
		"\r\n\t\t#data:hover {"
		"\r\n\t\t\tbackground-color: #F9D79E;"
		"\r\n\t\t}"
		"\r\n"
		"\r\n\t\t.info {"
		"\r\n\t\t\tfont-size: 1rem;"
		"\r\n\t\t\ttext-decoration: underline;"
		"\r\n\t\t}"
		"\r\n"
		"\r\n\t\t.hidden {"
		"\r\n\t\t\tdisplay: none;"
		"\r\n\t\t}"
		"\r\n"
		"\r\n\t\t.arrow {"
		"\r\n\t\t\tdisplay: inline-block;"
		"\r\n\t\t\tmargin-right: 8px;"
		"\r\n\t\t\ttransition: transform 0.3s ease;"
		"\r\n\t\t}"
		"\r\n"
		"\r\n\t\t.arrow.expanded {"
		"\r\n\t\t\ttransform: rotate(90deg);"
		"\r\n\t\t}"
		"\r\n"
		"\r\n\t\t.section-header {"
		"\r\n\t\t\tfont-size: 1rem;"
		"\r\n\t\t\tbackground-color: #F1C275;"
		"\r\n\t\t\tcursor: pointer;"
		"\r\n\t\t\ttop: 10px;"
		"\r\n\t\t\tposition: sticky;"
		"\r\n\t\t}"
		"\r\n\t</style>"

		"\r\n</head>"
		"\r\n<body>"
		"\r\n\t<header>"
		"\r\n\t\t<h1>VPlug</h1>"
		"\r\n\t</header>"
		"\r\n\t<div>"
		"\r\n\t\t<p>Отчет: незаполненные/отсутствующие параметры</p>"
		"\r\n\t\t<p>Путь/имя: " + path_+ "</p>"
		"\r\n\t</div>"
		"\r\n\t<table>"
		"\r\n\t\t<thead>"
		"\r\n\t\t\t<tr>"
		"\r\n\t\t\t\t<th scope=\"col\">ID</th>"
		"\r\n\t\t\t\t<th scope=\"col\">Имя</th>"
		"\r\n\t\t\t\t<th scope=\"col\">Параметр(ы)</th>"
		"\r\n\t\t\t</tr>"
		"\r\n\t\t</thead>"//?
		"\r\n\t\t<tbody>"
	);

	//Не обработать hidden категорию из 2-х слов
	for each(KeyValuePair<Tuple<String^, String^>^, List<Elements::BaseElement^>^>^ kvp in data) {
		output->Write("\r\n\t\t\t<tr class=\"section-header\" onclick=\"toggleSection('" + kvp->Key->Item2 + "')\">");
		output->Write("\r\n\t\t\t<td colspan=3><span class=\"arrow\">></span><span class=\"category\">" + kvp->Key->Item1 + "</span></td></tr>");

		for each(Elements::BaseElement^ element in kvp->Value) {
			output->Write(
				"\r\n\t\t\t<tr id=\"data\" class=\"hidden " + kvp->Key->Item2 + "-content\">" +
				"\r\n\t\t\t\t<td scope=\"row\">" + element->GetId() + "</td>"
				"\r\n\t\t\t\t<td>" + element->GetName() + "</td>"
				"\r\n\t\t\t\t<td><p class=\"info\">Не заполнен или отсутствует у элемента:</p>"
			);

			for each(KeyValuePair<String^, String^>^ param_value in element->GetParameters()) {
				output->Write("\r\n\t\t\t\t\t<p>" + param_value->Key + ": " + param_value->Value + "</p>");
			}

			output->Write(
				"\r\n\t\t\t\t</td>"
				"\r\n\t\t\t</tr>"
			);
		}
	}
	output->Write(
		"\r\n\t\t</tbody>"
		"\r\n\t</table>"
		"\r\n\t<script>"
		"\r\n\t\tfunction toggleSection(sectionName) {"
		"\r\n\t\t\tconst rows = document.querySelectorAll('.' + sectionName + '-content');"
		"\r\n\t\t\tconst header = event.currentTarget;"
		"\r\n\t\t\tconst arrow = header.querySelector('.arrow');"
		"\r\n\t\t\trows.forEach(row => {"
		"\r\n\t\t\t\trow.classList.toggle('hidden');"
		"\r\n\t\t\t});"
		"\r\n\t\t\tarrow.classList.toggle('expanded');"
		"\r\n\t\t\}"
		"\r\n\t</script>"
		"\r</body>"
		"\r</html>"
	);

	output->Close();
}