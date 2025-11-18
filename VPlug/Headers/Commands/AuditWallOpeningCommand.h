#pragma once

#include "../../Headers/UI/MyForms/FormAuditWallOpening.h"
#include "../../Headers/Revit/Services/WallService.h"

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;

using namespace Autodesk::Revit::UI;
using namespace Autodesk::Revit::DB;
using namespace Autodesk::Revit::Attributes;

namespace Commands {

public ref class AuditTypeWallSummary {
private:
	String^ name_;
	int totalWalls_;
	double totalArea_;
	int totalOpening_;
	double totalAreaWallsWithOpenings_;
	double totalAreaWallsWithoutOpenings_;

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

	Dictionary<String^, String^>^ filters_;
};

[Transaction(TransactionMode::Manual)]
public ref class AuditWallOpeningCommand : public IExternalCommand {
private:
	Document^ doc_;
	MyForm::FormAuditWallOpening^ form_;

	void SubscriptionEvent();

	void Audit(List<Tuple<int, String^, String^>^>^ numFilterValue);

	Dictionary<String^, AuditTypeWallSummary^>^ dataTypeWallSummary_;

public:
	virtual Result Execute(ExternalCommandData^ commandData,
		String^% message, ElementSet^ elements);
};

}//namespace Commands










