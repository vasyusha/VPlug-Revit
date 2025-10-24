#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace System::Drawing;

namespace MyForm {

enum class AuditStage {
	None,
	MethodSelected,
	Prepare,
	ConfigLoaded,
	ChecksSelected,
	Running,
	RunningDone,
	ExportPathLoaded,
	Export,
	ExportDone
};

public ref class AuditSummaryRow {
public:
	property String^ Scope;
	property int Total;
	property int Passed;
	property int Failed;
	property int MissedValue;
	property int NoParam;
};

public delegate void AuditMethodSelectedHandler(String^ method);
public delegate void AuditConfigLoadedHandler(String^ path);
public delegate void AuditChecksSelectedHandler(List<String^>^ selected);
public delegate void AuditRunningHandler();
public delegate void AuditExportHandler(String^ path);

public ref class FormAuditParameter : public Windows::Forms::Form {
private:
	AuditStage auditStage;

	String^ selectedMethod_;
	String^ configPath_;
	String^ exportPath_;

	List<AuditSummaryRow^>^ summaryRows_;

	Windows::Forms::ComboBox^ cbMethod_;
	Button^ btnPrepare_;

	Windows::Forms::TextBox^ tbConfig_;
	Button^ btnBrowseConfig_;

	Windows::Forms::Panel^ pnlChecks_;
	DataGridView^ dgvTable_;
	Button^ btnRun_;

	Windows::Forms::TextBox^ tbExport_;
	Button^ btnExportBrowse_;
	Button^ btnExport_;

	StatusStrip^ status_;
	ToolStripStatusLabel^ statusText_;

	void BuildUi();
	void SubscriptionEvent();
	void UpdateUiState();
	void SetStatus(String^ text);

	void OnMethodChanged(Object^ sender, EventArgs^ e);
	void OnPrepare(Object^ sender, EventArgs^ e);
	void OnBrowseConfig(Object^ sender, EventArgs^ e);
	void OnCheckBox(Object^ sender, EventArgs^ e);
	void OnRun(Object^ sender, EventArgs^ e);
	void OnBrowseExport(Object^ sender, EventArgs^ e);
	void OnExport(Object^ sender, EventArgs^ e);

public:
	FormAuditParameter();

	void AddRowTable(AuditSummaryRow^ row);

	event AuditMethodSelectedHandler^ MethodChanged;
	event AuditConfigLoadedHandler^ LoadConfigRequest;
	event AuditChecksSelectedHandler^ ChecksSelectedRequest;
	event AuditRunningHandler^ RunRequest;
	event AuditExportHandler^ ExportRequest;

	void SetAvailableMethods(IList<String^>^ methods);
	void SetChecks(IDictionary<String^, String^>^ checks);
	/*
	void MarkAuditPrepared(bool ok);
	void MarkAuditFinished(bool ok);
	*/

};

}//namespace MyForm