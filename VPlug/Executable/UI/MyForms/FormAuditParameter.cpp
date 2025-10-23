#include "../../../Headers/UI/MyForms/FormAuditParameter.h"

namespace MyForm {

FormAuditParameter::FormAuditParameter() {
	this->Text = "Проверка параметров";
	this->StartPosition = FormStartPosition::CenterScreen;
	this->Size = Drawing::Size(1000, 700);
    this->MinimumSize = Drawing::Size(900, 600);
    this->MaximumSize = Drawing::Size(1500, 1300);
    
    BuildUi();
}

void FormAuditParameter::BuildUi() {
	this->SuspendLayout();

    auto grid = gcnew TableLayoutPanel();
    grid->Dock = DockStyle::Fill;
    grid->AutoSize = true;
    grid->ColumnCount = 3;
    grid->RowCount = 3;
    grid->Padding = Windows::Forms::Padding(10);
    grid->ColumnStyles->Add(gcnew ColumnStyle(SizeType::AutoSize));
    grid->ColumnStyles->Add(gcnew ColumnStyle(SizeType::Percent, 100));
    grid->ColumnStyles->Add(gcnew ColumnStyle(SizeType::AutoSize));
    this->Controls->Add(grid);

    //Row 0
    Label^ lblMethod = gcnew Label();
    lblMethod->Text = "Метод проверки:";
    lblMethod->AutoSize = true;
    grid->Controls->Add(lblMethod, 0, 0);

    cbMethod_ = gcnew ComboBox();
    cbMethod_->DropDownStyle = ComboBoxStyle::DropDownList;
    cbMethod_->Dock = DockStyle::Fill;
    grid->Controls->Add(cbMethod_, 1, 0);

    btnPrepare_ = gcnew Button();
    btnPrepare_->Text = "Подготовить";
    grid->Controls->Add(btnPrepare_, 2, 0);

    //Row 1
    auto lblConfig = gcnew Label();
    lblConfig->Text = "Файл конфигурации:";
    lblConfig->AutoSize = true;
    grid->Controls->Add(lblConfig, 0, 1);

    tbConfig_ = gcnew TextBox();
    tbConfig_->Dock = DockStyle::Fill;
    tbConfig_->ReadOnly = true;
    grid->Controls->Add(tbConfig_, 1, 1);

    btnBrowseConfig_ = gcnew Button();
    btnBrowseConfig_->Text = "Выбрать…";
    grid->Controls->Add(btnBrowseConfig_, 2, 1);

    //Row 2
    pnlChecks_ = gcnew Panel();
    pnlChecks_->Width = 150;
    pnlChecks_->Dock = DockStyle::Fill;
    pnlChecks_->BackColor = Color::DarkGray;
    grid->Controls->Add(pnlChecks_, 0, 2);

    dgvTable_ = gcnew DataGridView();
    dgvTable_->Dock = DockStyle::Fill;
    dgvTable_->Columns->Add("Scope", "Проверка по");
    dgvTable_->Columns->Add("Name", "Имя");
    dgvTable_->Columns->Add("Total", "Всего");
    dgvTable_->Columns->Add("Passed", "Пройдено");
    dgvTable_->Columns->Add("Failed", "Не пройдено");
    dgvTable_->Columns->Add("MissedValue", "Не заполнено");
    dgvTable_->Columns->Add("NoParam", "Нет параметра");
    grid->Controls->Add(dgvTable_, 1, 2);

    btnRun_ = gcnew Button();
    btnRun_->Text = "Выполнить";
    grid->Controls->Add(btnRun_, 2, 2);

    auto exportPanel = gcnew TableLayoutPanel();
    exportPanel->Dock = DockStyle::Bottom;
    exportPanel->AutoSize = true;
    exportPanel->ColumnCount = 3;
    exportPanel->Padding = Windows::Forms::Padding(10);
    exportPanel->ColumnStyles->Add(gcnew ColumnStyle(SizeType::AutoSize));
    exportPanel->ColumnStyles->Add(gcnew ColumnStyle(SizeType::Percent, 100));
    exportPanel->ColumnStyles->Add(gcnew ColumnStyle(SizeType::AutoSize));
    this->Controls->Add(exportPanel);

    //Row 0 
    auto lblExport = gcnew Label();
    lblExport->Text = "Отчёт HTML:";
    lblExport->AutoSize = true;
    exportPanel->Controls->Add(lblExport, 0, 0);

    tbExport_ = gcnew TextBox();
    tbExport_->Dock = DockStyle::Fill;
    tbExport_->ReadOnly = true;
    exportPanel->Controls->Add(tbExport_, 1, 0);

    btnExportBrowse_ = gcnew Button();
    btnExportBrowse_->Text = "Сохранить…";
    exportPanel->Controls->Add(btnExportBrowse_, 2, 0);

    btnExport_ = gcnew Button();
    btnExport_->Text = "Сформировать отчёт";
    btnExport_->Dock = DockStyle::Right;
    exportPanel->Controls->Add(btnExport_, 2, 1);

    // Status bar
    status_ = gcnew StatusStrip();
    statusText_ = gcnew ToolStripStatusLabel();
    status_->Items->Add(statusText_);
    this->Controls->Add(status_);

	this->ResumeLayout(false);
}

}//namespace MyForm