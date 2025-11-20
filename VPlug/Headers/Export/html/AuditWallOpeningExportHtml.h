#pragma once

using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace System::Collections::Generic;

namespace ExportHtml {

namespace WallOpening {

public ref class DataOpening {
private:
	String^ name_;
	int id_;
	String^ categoryName_;

public:
	property String^ Name {
		String^ get();
		void set(String^ value);
	};

	property int Id {
		int get();
		void set(int value);
	};

	property String^ CategoryName {
		String^ get();
		void set(String^ value);
	};
};

public ref class ReportElementWall {
private:
	String^ name_;
	int id_;
	String^ categoryName_;
	double area_;
	int countOpening_;
	IList<DataOpening^>^ dataOpenings_;

public:
	property String^ Name {
		String^ get();
		void set(String^ value);
	};

	property int Id {
		int get();
		void set(int value);
	};

	property String^ CategoryName {
		String^ get();
		void set(String^ value);
	};

	property double Area {
		double get();
		void set(double value);
	};

	property int CountOpening {
		int get();
		void set(int value);
	};

	property IList<DataOpening^>^ DataOpenings {
		IList<DataOpening^>^ get();
		void set(IList<DataOpening^>^ value);
	};
};


public ref class ReportTypeWall {
private:
	String^ name_;
	int totalWalls_;
	double totalArea_;
	int totalOpening_;
	double totalAreaWallsWithOpenings_;
	double totalAreaWallsWithoutOpenings_;

public:
	property String^ Name {
		String^ get();
		void set(String^ value);
	};

	property int TotalWalls {
		int get();
		void set(int value);
	};

	property double TotalArea {
		double get();
		void set(double value);
	};

	property int TotalOpening {
		int get();
		void set(int value);
	};

	property double TotalAreaWallsWithOpenings {
		double get();
		void set(double value);
	};

	property double TotalAreaWallsWithoutOpenings {
		double get();
		void set(double value);
	};
};


public ref class ReportModel {
private:
	String^ filePath_;
	String^ projectName_;
	String^ dataTimeStr_;

	IList<ReportTypeWall^>^ typeWall_;
	IList<ReportElementWall^>^ elemetnWall_;
public:
	ReportModel();

	property String^ FilePath {
		String^ get();
		void set(String^ value);
	};

	property String^ ProjectName {
		String^ get();
		void set(String^ value);
	};

	property String^ DataTimeStr {
		String^ get();
		void set(String^ value);
	};

	property IList<ReportTypeWall^>^ DataTypeWall {
		IList<ReportTypeWall^>^ get();
		void set(IList<ReportTypeWall^>^ value);
	};

	property IList<ReportElementWall^>^ DataElementWall {
		IList<ReportElementWall^>^ get();
		void set(IList<ReportElementWall^>^ value);
	};

};

public ref class AuditWallOpeningExportHtml {
private:
	void AppendHeader(StringBuilder^ sb, ReportModel^ model);
	void AppendBody(StringBuilder^ sb, ReportModel^ model);

public:
	String^ BuildHtml(ReportModel^ model);	
	void SaveHtmlToFile(ReportModel^ model, String^ path);

};

}//namespace WallOpening

}//namespace ExportHtml