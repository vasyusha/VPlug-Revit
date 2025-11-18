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
	FiltersAreFull,
	Running,
	RunningDone,
	ExportPathLoaded,
	Export,
	ExportDone
};

public delegate void AuditWallOpeningRunningHandler(List<Tuple<int, String^, String^>^>^ numFilterValue);

public ref class FormAuditWallOpening : public Windows::Forms::Form {
private:
	AuditStageWallOpening auditStage_;

	NumericUpDown^ nudCountFilters_;

	Button^ btnSetCountFilters_;

	TableLayoutPanel^ gridFilters_;

	Button^ btnRun_;

	DataGridView^ dgvTable_;

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
};



}//namespace MyForm















