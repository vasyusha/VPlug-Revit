#pragma once

#include "../../Domain/WallOpeningDomain.h"

using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace System::Collections::Generic;

namespace ExportHtml {

public ref class AuditWallOpeningExportHtml {
private:
	void AppendHeader(StringBuilder^ sb, MyDomain::WallOpening::WallOpeningReport^ report);
	void AppendBody(StringBuilder^ sb, MyDomain::WallOpening::WallOpeningReport^ report);

public:
	String^ BuildHtml(MyDomain::WallOpening::WallOpeningReport^ report);	
	void SaveHtmlToFile(MyDomain::WallOpening::WallOpeningReport^ report, String^ path);

};

}//namespace ExportHtml