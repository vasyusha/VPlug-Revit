#pragma once

#include "../../Domain/ReportDomain.h"

using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace System::Collections::Generic;

namespace ExportHtml {

public ref class AuditParameterExportHtml {
private:
	void AppendHeader(StringBuilder^ sb, MyDomain::AuditParameterReport::ResultReport^ resultReport);
	void AppendBody(StringBuilder^ sb, MyDomain::AuditParameterReport::ResultReport^ resultReport);
	void AppendSection(StringBuilder^ sb, MyDomain::AuditParameterReport::ResultReport^ resultReport);

public:
	String^ BuildHtml(MyDomain::AuditParameterReport::ResultReport^ resultReport);
	void SaveHtmlToFile(MyDomain::AuditParameterReport::ResultReport^ resultReport, String^ path);

};

}
