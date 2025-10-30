#pragma once

using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace System::Collections::Generic;

namespace ExportHtml {

public ref class RequirementRow {
public:
	RequirementRow();

	property int Id;
	property String^ Name;
	property bool Pass;

	ref struct Param{
		String^ Name;
		String^ Value;
		bool Filled;
	};

	List<Param^>^ Params;
};

public ref class CategoryReport {
private:
	String^ name_;
	String^ slug_;
	bool pass_;
	int checksPass_;
	int checksTotal_;
	int elementsPass_;
	int elementsTotal_;
	int percent_;

public:
	CategoryReport();

	property String^ Name {
		String^ get();
		void set(String^ value);
	};

	property String^ Slug {
		String^ get();
		void set(String^ value);
	};

	property bool Pass {
		bool get();
		void set(bool value);
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
	List<String^>^ CheckedParameters;
};

public ref class ReportModel {
private:
	bool pass_;
	int specPass_;
	int specTotal_;
	int reqPass_;
	int reqTotal_;
	int checkPass_;
	int checkTotal_;
	int percent_;

public:
	ReportModel();

	property String^ FilePath;
	property String^ ProjectName;
	property String^ DataTimeStr;

	property bool Pass {
		bool get();
		void set(bool value);
	};

	property int SpecPass {
		int get();
		void set(int value);
	};

	property int SpecTotal {
		int get();
		void set(int value);
	};

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

	property int Percent {
		int get();
		void set(int value);
	};

	List<CategoryReport^>^ Categories;
};

public ref class AuditParameterExportHtml {
private:
	void AppendHeader(StringBuilder^ sb, ReportModel^ model);
	void AppendBody(StringBuilder^ sb, ReportModel^ model);
	void AppendSection(StringBuilder^ sb, ReportModel^ model);

public:
	String^ BuildHtml(ReportModel^ model);
	void SaveHtmlToFile(ReportModel^ model, String^ path);

};

}
