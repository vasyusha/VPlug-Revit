#pragma once

using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;

namespace ExportHtml {

public ref class RequirementRow {
public:
	String^ Title;
	bool Pass;

	ref struct Row {
		int Id;
		String^ Name;
		String^ Comment;
	};

	List<Row^> Rows;
};

public ref class CategoryReport {
public:
	String^ Name;
	String^ Slug;
	int ChecksPass;
	int ChecksTotal;
	int ElementsPass;
	int ElementsTotal;
	int Percent;
	List<RequirementRow^>^ Requirements;
};

public ref class ReportMode {
public:
	String^ FilePath;
	String^ ProjectName;
	String^ DataTime;
	int ReqPass;
	int ReqTotal;
	int CheckPass;
	int CheckTotal;
	int ElPass;
	int ElTotal;
	int Percent;
	List<CategoryReport^>^ Categories;
};

public ref class AuditParameterExportHtml {
private:

public:

};

}
