#pragma once

using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;

namespace ExportHtml {

public ref class RequirementRow {
public:
	RequirementRow();

	property String^ Title;
	property bool Pass;

	ref struct Row {
		int Id;
		String^ Name;
		String^ Comment;
	};

	List<Row^>^ Rows;
};

public ref class CategoryReport {
private:
	int checksPass_;
	int checksTotal_;
	int elementsPass_;
	int elementsTotal_;
	int percent_;
	String^ slug_;

public:
	CategoryReport();

	property String^ Name;

	property String^ Slug {
		String^ get();
		void set(String^ value);
	};

	property int ChecksPass {
		int get();
		void set(int value);
	};

	property int ChecksTotal {
		int get();
		void set(int value);
	};

	property int ElementsPass {
		int get();
		void set(int value);
	};

	property int ElementsTotal {
		int get();
		void set(int value);
	};

	property int Percent {
		int get();
		void set(int value);
	};

	List<RequirementRow^>^ Requirements;
};

public ref class ReportModel {
private:
	int reqPass_;
	int reqTotal_;
	int checkPass_;
	int checkTotal_;
	int elPass_;
	int elTotal_;
	int percent_;

public:
	ReportModel();

	property String^ FilePath;
	property String^ ProjectName;
	property String^ DataTimeStr;

	property int ReqPass {
		int get();
		void set(int value);
	};

	property int ReqTotal {
		int get();
		void set(int value);
	};

	property int CheckPass {
		int get();
		void set(int value);
	};

	property int CheckTotal {
		int get();
		void set(int value);
	};

	property int ElPass {
		int get();
		void set(int value);
	};

	property int ElTotal {
		int get();
		void set(int value);
	};

	property int Percent {
		int get();
		void set(int value);
	};

	List<CategoryReport^>^ Categories;
};

public ref class AuditParameterExportHtml {
private:

public:

};

}
