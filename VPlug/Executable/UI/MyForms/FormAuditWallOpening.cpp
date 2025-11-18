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
	grid->Controls->Add(gridTop);
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
	grid->Controls->Add(gridFilters_);

	btnRun_ = gcnew Button();
	btnRun_->Anchor = AnchorStyles::Top | AnchorStyles::Right;
	btnRun_->Text = "Выполнить";
	//btnRun_->Enabled = false;
	btnRun_->Visible = false;
	grid->Controls->Add(btnRun_, 0, 3);

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
	grid->Controls->Add(dgvTable_, 0, 4);

	TableLayoutPanel^ gridExport = gcnew TableLayoutPanel();
	gridExport->Dock = DockStyle::Bottom;
	gridExport->AutoSize = true;

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

void FormAuditWallOpening::SubscriptionEvent() {
	nudCountFilters_->ValueChanged += gcnew EventHandler(this, &FormAuditWallOpening::OnValueChanged);
	btnSetCountFilters_->Click += gcnew EventHandler(this, &FormAuditWallOpening::OnSetCountFilters);
	btnRun_->Click += gcnew EventHandler(this, &FormAuditWallOpening::OnRun);
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

void FormAuditWallOpening::UpdateUiState() {
	btnRun_->Visible = auditStage_ == AuditStageWallOpening::FiltersCreated ? true : false;

}

void FormAuditWallOpening::SetStatus(String^ text) {
	statusText_->Text = text;
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
		RunRequest(numFilterValue);
	}
}

void FormAuditWallOpening::OnValueChanged(Object^ sender, EventArgs^ e) {
	if (nudCountFilters_->Value > 0 && nudCountFilters_->Value < 10) {
		auditStage_ = AuditStageWallOpening::NumberFiltersInstalled;
		SetStatus("Кол-во фильтров установленно");
	} else {
		auditStage_ = AuditStageWallOpening::None;
		SetStatus("Установите кол-во фильтров");
	}
}

void FormAuditWallOpening::AddRowTable(String^ name, 
		String^ totalWalls,
		String^ totalArea, 
		String^ totalAreaHasOnening,
		String^ totalAreaNoOpening,
		String^ totalOpening
)
 {
	dgvTable_->Rows->Add(
		name,
		totalWalls,
		totalArea,
		totalAreaHasOnening,
		totalAreaNoOpening,
		totalOpening
	);
}

}//namespace MyForm