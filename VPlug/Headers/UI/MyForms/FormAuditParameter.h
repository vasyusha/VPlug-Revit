#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace System::Drawing;

namespace MyForm {

enum class AuditStage {
	None,
	MehtodSelected,
	ConfigLoaded,
	ChecksSelected,
	Running,
	RunningDone,
	Export,
	ExportDone
};

public ref class AuditSummaryRow {
public:
	property String^ Scope;
	property String^ Name;
	property int Total;
	property int Passed;
	property int Failed;
	property int MissedValue;
	property int NoParam;
};

public delegate void AuditMethodSelectedHandler(String^ method);
public delegate void AuditConfigLoadedHandler(String^ path);
public delegate void AuditChecksSelectedHandler();
public delegate void AuditRunningHandler();
public delegate void AuditExportHandler(String^ path);

public ref class FormAuditParameter : public Windows::Forms::Form{
private:
	AuditStage auditStage;
	
	String^ selectedMethod_;
	String^ configPath_;
	String^ exportPath_;

	List<AuditSummaryRow^>^ summaryRows_;

	void BuildUi();


public:
	FormAuditParameter();

};




}//namespace MyForm