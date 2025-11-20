#pragma once

#include "../../Headers/UI/MyForms/FormAuditWallOpening.h"
#include "../../Headers/Revit/Services/WallService.h"
#include "../../Headers/Export/html/AuditWallOpeningExportHtml.h"

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;

using namespace Autodesk::Revit::UI;
using namespace Autodesk::Revit::DB;
using namespace Autodesk::Revit::Attributes;

namespace Commands {

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

public ref class AuditElementWall {
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

public ref class AuditTypeWallSummary {
private:
	String^ name_;
	int totalWalls_;
	double totalArea_;
	int totalOpening_;
	double totalAreaWallsWithOpenings_;
	double totalAreaWallsWithoutOpenings_;
	IList<DataOpening^>^ dataOpenings_;

public:

	AuditTypeWallSummary();

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

	property IList<DataOpening^>^ DataOpenings {
		IList<DataOpening^>^ get();
		void set(IList<DataOpening^>^ value);
	};

	Dictionary<String^, String^>^ filters_;
};

[Transaction(TransactionMode::Manual)]
public ref class AuditWallOpeningCommand : public IExternalCommand {
private:
	Document^ doc_;
	MyForm::FormAuditWallOpening^ form_;

	void SubscriptionEvent();

	void Audit(List<Tuple<int, String^, String^>^>^ numFilterValue);

	void FillTable();

	void ExportPrepareData(ExportHtml::WallOpening::ReportModel^ repModel);
	void Export(String^ path);

	Dictionary<String^, AuditTypeWallSummary^>^ dataTypeWallSummary_;
	IList<AuditElementWall^>^ dataElementWall_;

public:
	virtual Result Execute(ExternalCommandData^ commandData,
		String^% message, ElementSet^ elements);
};

}//namespace Commands










