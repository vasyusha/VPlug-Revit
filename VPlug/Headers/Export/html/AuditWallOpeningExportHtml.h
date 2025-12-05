#pragma once

#include "../../Domain/ReportDomain.h"

using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace System::Collections::Generic;

namespace ExportHtml {

public ref class AuditWallOpeningExportHtml {
private:
	void AppendHeader(StringBuilder^ sb, MyDomain::AuditWallOpeningsReport::ResultReport^ resultReport);
	void AppendBody(StringBuilder^ sb, MyDomain::AuditWallOpeningsReport::ResultReport^ resultReport);

public:
	String^ BuildHtml(MyDomain::AuditWallOpeningsReport::ResultReport^ resultReport);	
	void SaveHtmlToFile(MyDomain::AuditWallOpeningsReport::ResultReport^ resultReport, String^ path);

};

}//namespace ExportHtml