#include "..\..\..\Headlines\Export\html\AuditParameter_htmlExport.h"

Export::AuditParameterHtmlExport::AuditParameterHtmlExport(String^ path) : path_(path) {

};

void Export::AuditParameterHtmlExport::CompileFile(Dictionary<String^, List<Elements::BaseElement^>^>^ data) {

	StreamWriter^ output = gcnew StreamWriter(path_);

	output->Write(
		"<!doctype html>"
		"\r\n<head>"
		"\r\n\t<meta charset=\"utf - 8\" />"
		"\r\n\t\<title>Отчет</title>"
		"\r\n\t<style>"
		"\r\n\t\thtml {"
		"\r\n\t\t\tbackground: rgb(195 195 150);"
		"\r\n\t\t}"
		"\r\n"
		"\r\n\t\ttable {"
		"\r\n\t\t\twidth: 100%;"
		"\r\n\t\t\tborder-collapse: collapse;"
		"\r\n\t\t\tborder: 4px solid rgb(140 140 140);"
		"\r\n\t\t\tfont-family: sans-serif;"
		"\r\n\t\t\tfont-size: 0.8rem;"
		"\r\n\t\t\tletter-spacing: 1px;"
		"\r\n\t\t}"
		"\r\n"
		"\r\n\t\t.info {"
		"\r\n\t\t\tfont-size: 1rem;"
		"\r\n\t\t\ttext-decoration: underline;"
		"\r\n\t\t}"
		"\r\n"
		"\r\n\t\t.category {"
		"\r\n\t\t\tfont-size: 1rem;"
		"\r\n\t\t\ttext-align: center;"
		"\r\n\t\t}"
		"\r\n"
		"\r\n\t\t.state {"
		"\r\n\t\t\tfont-size: 0.9rem;"
		"\r\n\t\t}"
		"\r\n"
		"\r\n\t\tthead {"
		"\r\n\t\t\tborder-collapse: collapse;"
		"\r\n\t\t\tborder: 4px solid rgb(140 140 140);"
		"\r\n\t\t}"
		"\r\n"
		"\r\n\t\tthead,"
		"\r\n\t\ttfoot {"
		"\r\n\t\t\tbackground-color: rgb(228 240 245);"
		"\r\n\t\t}"
		"\r\n"
		"\r\n\t\tth,"
		"\r\n\t\ttd {"
		"\r\n\t\t\tborder: 2px solid rgb(160 160 160);"
		"\r\n\t\t\tpadding: 8px 10px;"
		"\r\n\t\t}"
		"\r\n"
		"\r\n\t\ttd:last-of-type {"
		"\r\n\t\t\ttext-align: left;"
		"\r\n\t\t}"
		"\r\n"
		"\r\n\t\ttr {"
		"\r\n\t\t\tbackground: rgb(195 195 170);"
		"\r\n\t\t}"
		"\r\n"
		"\r\n\t\ttfoot th {"
		"\r\n\t\t\ttext-align: Right;"
		"\r\n\t\t}"
		"\r\n"
		"\r\n\t\ttfoot td {"
		"\r\n\t\t\tfont-weight: bold;"
		"\r\n\t\t}"
		"\r\n\t</style>"

		"\r\n</head>"
		"\r\n<body>"
		"\r\n\t<header>"
		"\r\n\t\t<h2>Отчет: незаполненные/отсутствующие параметры</h2>"
		"\r\n\t\t<h3>Путь/имя: " + path_+
		"\r\n\t</header>"
		"\r\n\t<table>"
		"\r\n\t\t<thead>"
		"\r\n\t\t<tbody>"
		"\r\n\t\t\t<tr>"
		"\r\n\t\t\t\t<th scope=\"col\">ID</th>"
		"\r\n\t\t\t\t<th scope=\"col\">Имя</th>"
		"\r\n\t\t\t\t<th scope=\"col\">Параметр(ы)</th>"
		"\r\n\t\t\t</tr>"
		"\r\n\t\t</thead>"//?
	);


	for each(KeyValuePair<String^, List<Elements::BaseElement^>^>^ kvp in data) {
		output->Write("\r\n\t\t\t<td colspan=3><p class=\"category\">" + kvp->Key + "</p></td>");

		for each(Elements::BaseElement^ element in kvp->Value) {
			output->Write(
				"\r\n\t\t\t<tr>" +
				"\r\n\t\t\t\t<th scope=\"row\">" + element->GetId() + "</th>"
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
		"\r</body>"
		"\r</html>"
	);

	output->Close();
}