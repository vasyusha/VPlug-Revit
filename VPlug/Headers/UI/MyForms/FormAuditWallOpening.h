#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace System::Drawing;

namespace MyForm {

enum class AuditStageWallOpening {
	None,
	NumberFiltersInstalled,
	FiltersCreated,
	Running,
	RunningDone,
	ExportPathLoaded,
	Export,
	ExportDone
};

public delegate void AuditWallOpeningRunningHandler(List<Tuple<int, String^, String^>^>^ numFilterValue);
public delegate void AuditWallOpeningExportHandler(String^ path);

public ref class FormAuditWallOpening : public Windows::Forms::Form {
private:
	AuditStageWallOpening auditStage_;

	String^ exportPath_;

	NumericUpDown^ nudCountFilters_;

	Button^ btnSetCountFilters_;

	TableLayoutPanel^ gridFilters_;

	Button^ btnRun_;

	DataGridView^ dgvTable_;

	Windows::Forms::TextBox^ tbExport_;
	Button^ btnExportBrows_;
	Button^ btnExport_;

	StatusStrip^ status_;
	ToolStripStatusLabel^ statusText_;

	void BuildUi();
	void BuildUiFilters(int quantity);
	void SubscriptionEvent();
	void UpdateUiState();
	void SetStatus(String^ text);

	void OnValueChanged(Object^ sender, EventArgs^ e);
	void OnSetCountFilters(Object^ sender, EventArgs^ e);
	void OnRun(Object^ sender, EventArgs^ e);
	void OnBrowsExport(Object^ sender, EventArgs^ e);
	void OnExport(Object^ sender, EventArgs^ e);

public:
	FormAuditWallOpening();

	void AddRowTable(String^ name,
		String^ totalWalls,
		String^ totalArea,
		String^ totalAreaHasOnening,
		String^ totalAreaNoOpening,
		String^ totalOpening
	);//test

	event AuditWallOpeningRunningHandler^ RunRequest;
	event AuditWallOpeningExportHandler^ ExportRequest;

	void MarkAuditFinished(bool ok);
	void MarkAuditExportFinished(bool ok);
};

}//namespace MyForm