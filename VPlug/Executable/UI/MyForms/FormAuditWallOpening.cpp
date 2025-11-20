#include "../../../Headers/UI/MyForms/FormAuditWallOpening.h"

namespace MyForm {

FormAuditWallOpening::FormAuditWallOpening() {
	this->Text = "Проверка проёмов у стен";
	this->StartPosition = FormStartPosition::CenterScreen;
	this->AutoScroll = true;
	this->Size = Drawing::Size(1000, 700);
	this->MinimumSize = Drawing::Size(900, 600);
	this->MaximumSize = Drawing::Size(1500, 1300);

	auditStage_ = AuditStageWallOpening::None;

	BuildUi();
	SubscriptionEvent();
	UpdateUiState();
	SetStatus("Установите кол-во фильтров");
}

void FormAuditWallOpening::BuildUi() {
	this->SuspendLayout();

	TableLayoutPanel^ grid = gcnew TableLayoutPanel();
	grid->Dock = DockStyle::Fill;
	grid->AutoSize = true;
	grid->ColumnCount = 1;
	grid->RowCount = 4;
	grid->Padding = Windows::Forms::Padding(10);
	grid->ColumnStyles->Add(gcnew ColumnStyle(SizeType::Percent, 100));
	grid->RowStyles->Add(gcnew RowStyle(SizeType::AutoSize));
	grid->RowStyles->Add(gcnew RowStyle(SizeType::AutoSize));
	grid->RowStyles->Add(gcnew RowStyle(SizeType::AutoSize));
	grid->RowStyles->Add(gcnew RowStyle(SizeType::Percent, 100));

	TableLayoutPanel^ gridTop = gcnew TableLayoutPanel();
	gridTop->Dock = DockStyle::Top;
	gridTop->AutoSize = true;
	gridTop->ColumnCount = 4;
	gridTop->RowCount = 1;
	gridTop->Padding = Windows::Forms::Padding(10);
	gridTop->ColumnStyles->Add(gcnew ColumnStyle(SizeType::AutoSize));
	gridTop->ColumnStyles->Add(gcnew ColumnStyle(SizeType::Percent, 50));
	gridTop->ColumnStyles->Add(gcnew ColumnStyle(SizeType::Percent, 50));
	gridTop->ColumnStyles->Add(gcnew ColumnStyle(SizeType::AutoSize));
	grid->Controls->Add(gridTop, 0, 0);
	this->Controls->Add(grid);

	//Row 0
	Label^ lblCountFilter = gcnew Label();
	lblCountFilter->Text = "Кол-во фильтров:";
	lblCountFilter->AutoSize = true;
	gridTop->Controls->Add(lblCountFilter, 0, 0);

	nudCountFilters_ = gcnew NumericUpDown();
	nudCountFilters_->ReadOnly = true;
	gridTop->Controls->Add(nudCountFilters_, 1, 0);

	btnSetCountFilters_ = gcnew Button();
	btnSetCountFilters_->Text = "Подготовить";
	btnSetCountFilters_->AutoSize = true;
	gridTop->Controls->Add(btnSetCountFilters_, 4, 0);

	gridFilters_ = gcnew TableLayoutPanel();
	gridFilters_->Dock = DockStyle::Top;
	gridFilters_->AutoSize = true;
	gridFilters_->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
	gridFilters_->GrowStyle = TableLayoutPanelGrowStyle::AddRows;
	gridFilters_->ColumnCount = 4;
	gridFilters_->Margin = Windows::Forms::Padding(0, 0, 0, 20);
	gridFilters_->ColumnStyles->Add(gcnew ColumnStyle(SizeType::AutoSize));
	gridFilters_->ColumnStyles->Add(gcnew ColumnStyle(SizeType::Percent, 50));
	gridFilters_->ColumnStyles->Add(gcnew ColumnStyle(SizeType::Percent, 50));
	gridFilters_->ColumnStyles->Add(gcnew ColumnStyle(SizeType::AutoSize));
	grid->Controls->Add(gridFilters_, 0, 1);

	btnRun_ = gcnew Button();
	btnRun_->Anchor = AnchorStyles::Top | AnchorStyles::Right;
	btnRun_->Text = "Выполнить";
	//btnRun_->Enabled = false;
	btnRun_->Visible = false;
	grid->Controls->Add(btnRun_, 0, 2);

	dgvTable_ = gcnew DataGridView();
	dgvTable_->Dock = DockStyle::Fill;
	dgvTable_->ReadOnly = true;
	dgvTable_->AllowUserToAddRows = false;
	dgvTable_->RowHeadersVisible = false;
	dgvTable_->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
	//dgvTable_->Columns->Add("NumFilters", "Номер по фильтру");
	dgvTable_->Columns->Add("NameType", "Имя типа");
	dgvTable_->Columns->Add("CountExample", "Кол-во экземпляров(всего)");
	dgvTable_->Columns->Add("TotalArea", "Сумма площадей(общая)");
	dgvTable_->Columns->Add("TotalArea", "Сумма площадей(c проёмами)");
	dgvTable_->Columns->Add("TotalArea", "Сумма площадей(без проёмов)");
	dgvTable_->Columns->Add("quantityOpening", "Кол-во проёмов");
	grid->Controls->Add(dgvTable_, 0, 3);

	TableLayoutPanel^ gridExport = gcnew TableLayoutPanel();
	gridExport->Dock = DockStyle::Bottom;
	gridExport->AutoSize = true;
	gridExport->ColumnCount = 4;
	gridExport->RowCount = 2;
	gridExport->Padding = Windows::Forms::Padding(10);
	gridExport->ColumnStyles->Add(gcnew ColumnStyle(SizeType::AutoSize));
	gridExport->ColumnStyles->Add(gcnew ColumnStyle(SizeType::Percent, 65));
	gridExport->ColumnStyles->Add(gcnew ColumnStyle(SizeType::AutoSize));
	gridExport->ColumnStyles->Add(gcnew ColumnStyle(SizeType::AutoSize));
	grid->Controls->Add(gridExport, 0, 4);

	Label^ lblExport = gcnew Label();
	lblExport->Text = "Экспорт";
	lblExport->AutoSize = true;
	gridExport->Controls->Add(lblExport, 0, 0);

	tbExport_ = gcnew Windows::Forms::TextBox();
	tbExport_->Dock = DockStyle::Fill;
	tbExport_->ReadOnly = true;
	gridExport->Controls->Add(tbExport_, 1, 0);

	btnExportBrows_ = gcnew Button();
	btnExportBrows_->Text = "Сохранить...";
	btnExportBrows_->AutoSize = true;
	btnExportBrows_->Dock = DockStyle::Right;
	gridExport->Controls->Add(btnExportBrows_, 3, 0);

	btnExport_ = gcnew Button();
	btnExport_->Text = "Сформировать отчёт";
	btnExport_->AutoSize = true;
	gridExport->Controls->Add(btnExport_, 3, 1);

	//Status bar
	status_ = gcnew StatusStrip();
	statusText_ = gcnew ToolStripStatusLabel();
	status_->Items->Add(statusText_);
	this->Controls->Add(status_);

	this->ResumeLayout(false);
}

void FormAuditWallOpening::BuildUiFilters(int quantity) {
	for (int i = 0; i < quantity; ++i) {
		gridFilters_->RowCount += 1;

		Label^ lblFilter = gcnew Label();
		lblFilter->Text = String::Format("Филтер/Знач: {0}", i);
		gridFilters_->Controls->Add(lblFilter, 0, i);

		TextBox^ tbFilterParam = gcnew TextBox();
		tbFilterParam->Name = String::Format("Filter{0}", i);
		tbFilterParam->AutoSize = true;
		tbFilterParam->Dock = DockStyle::Fill;
		gridFilters_->Controls->Add(tbFilterParam, 1, i);

		TextBox^ tbFilterValue = gcnew TextBox();
		tbFilterValue->Name = String::Format("Value{0}", i);
		tbFilterValue->AutoSize = true;
		tbFilterValue->Dock = DockStyle::Fill;
		gridFilters_->Controls->Add(tbFilterValue, 2, i);
	}
}

void FormAuditWallOpening::UpdateUiState() {
	nudCountFilters_->Enabled =
		(auditStage_ == AuditStageWallOpening::None) ||
		(auditStage_ == AuditStageWallOpening::NumberFiltersInstalled);

	btnSetCountFilters_->Enabled = auditStage_ == AuditStageWallOpening::NumberFiltersInstalled;

	btnRun_->Visible = auditStage_ == AuditStageWallOpening::FiltersCreated;

	btnExportBrows_->Enabled = auditStage_ == AuditStageWallOpening::RunningDone;
	btnExport_->Enabled = auditStage_ == AuditStageWallOpening::ExportPathLoaded;
}

void FormAuditWallOpening::SetStatus(String^ text) {
	statusText_->Text = text;
}

void FormAuditWallOpening::SubscriptionEvent() {
	nudCountFilters_->ValueChanged += gcnew EventHandler(this, &FormAuditWallOpening::OnValueChanged);
	btnSetCountFilters_->Click += gcnew EventHandler(this, &FormAuditWallOpening::OnSetCountFilters);
	btnRun_->Click += gcnew EventHandler(this, &FormAuditWallOpening::OnRun);
	btnExportBrows_->Click += gcnew EventHandler(this, &FormAuditWallOpening::OnBrowsExport);
	btnExport_->Click += gcnew EventHandler(this, &FormAuditWallOpening::OnExport);
}
void FormAuditWallOpening::OnValueChanged(Object^ sender, EventArgs^ e) {
	if (nudCountFilters_->Value > 0 && nudCountFilters_->Value < 10) {
		auditStage_ = AuditStageWallOpening::NumberFiltersInstalled;
		SetStatus("Кол-во фильтров установленно");
	} else {
		auditStage_ = AuditStageWallOpening::None;
		SetStatus("Установите кол-во фильтров");
	}
	UpdateUiState();
}

void FormAuditWallOpening::OnSetCountFilters(Object^ sender, EventArgs^ e) {
	if (auditStage_ == AuditStageWallOpening::NumberFiltersInstalled) {
		gridFilters_->Controls->Clear();

		BuildUiFilters(static_cast<int>(nudCountFilters_->Value));

		auditStage_ = AuditStageWallOpening::FiltersCreated;
		SetStatus("Фильтры созданы");
		UpdateUiState();
	} else {
		MessageBox::Show(this, "Установите кол-во фильтров > 0 && < 10", "Внимание");
	}
}

void FormAuditWallOpening::OnRun(Object^ sender, EventArgs^ e) {
	List<Tuple<int, String^, String^>^>^ numFilterValue = gcnew List<Tuple<int, String^, String^>^>();

	for (int i = 0; i <= nudCountFilters_->Value; ++i) {
		TextBox^ filterTb = dynamic_cast<TextBox^>(gridFilters_->Controls[String::Format("Filter{0}", i)]);
		TextBox^ valueTb = dynamic_cast<TextBox^>(gridFilters_->Controls[String::Format("Value{0}", i)]);

		if (filterTb != nullptr && valueTb != nullptr) {
			if (!String::IsNullOrEmpty(filterTb->Text) && !String::IsNullOrEmpty(valueTb->Text)) {
				numFilterValue->Add(gcnew Tuple<int, String^, String^>(i, filterTb->Text, valueTb->Text));
			}
		}
	}

	if (numFilterValue->Count > 0) {
		auditStage_ = AuditStageWallOpening::Running;
		SetStatus("Проверка...");
		RunRequest(numFilterValue);
	} else {
		auditStage_ = AuditStageWallOpening::FiltersCreated;
		SetStatus("Ошибка запуска проверки, проверь фильтры!");
	}
}

void FormAuditWallOpening::OnBrowsExport(Object^ sender, EventArgs^ e) {
	SaveFileDialog^ dlg = gcnew SaveFileDialog();
	dlg->Filter = "HTML (*.html)|*.html|All files (*.*)|*.*";
	dlg->RestoreDirectory = true;

	if (dlg->ShowDialog(this) == ::DialogResult::OK) {
		exportPath_ = dlg->FileName;
		tbExport_->Text = exportPath_;

		auditStage_ = AuditStageWallOpening::ExportPathLoaded;

		UpdateUiState();
		SetStatus("Выбран путь для отчёта");
	}
}

void FormAuditWallOpening::OnExport(Object^ sender, EventArgs^ e) {
	if (String::IsNullOrWhiteSpace(exportPath_)) {
		MessageBox::Show(this, "Выберите путь для сохранения отчёта", "Внимание",
			MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return;
	}

	auditStage_ == AuditStageWallOpening::Export;
	SetStatus("Экспорт запущен");
	ExportRequest(exportPath_);
}

void FormAuditWallOpening::AddRowTable(String^ name,
	String^ totalWalls,
	String^ totalArea,
	String^ totalAreaHasOnening,
	String^ totalAreaNoOpening,
	String^ totalOpening
) {
	dgvTable_->Rows->Add(
		name,
		totalWalls,
		totalArea,
		totalAreaHasOnening,
		totalAreaNoOpening,
		totalOpening
	);
}

void FormAuditWallOpening::MarkAuditFinished(bool ok) {
	auditStage_ = ok ? AuditStageWallOpening::RunningDone : AuditStageWallOpening::Running;
	SetStatus(ok ? "Проверка произведена" : "Ошибка проверки");
	UpdateUiState();
}

void FormAuditWallOpening::MarkAuditExportFinished(bool ok) {
	auditStage_ = ok ? AuditStageWallOpening::ExportDone : AuditStageWallOpening::Export;
	SetStatus(ok ? "Экспорт завершен" : "Ошибка экспорта");
	UpdateUiState();
}

}//namespace MyForm
