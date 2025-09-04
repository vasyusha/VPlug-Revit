#include "..\..\..\Headlines\UI\VPForms\VPFormAuditParameterCommand.h"

VPForms::VPFormAuditParameterCommand::VPFormAuditParameterCommand() {
	this->Name = "audit_parameter";
	this->Text = "Инструментарий";
	this->Location = Drawing::Point(2500, 2500);
	this->Size = Drawing::Size(1000, 750);
	this->FormBorderStyle = ::FormBorderStyle::FixedSingle;
	this->MinimizeBox = false;

	CreateControls();
}

void VPForms::VPFormAuditParameterCommand::CreateControls() {
	CreateButton();
	CreateTextBox();
	CreateLabel();
	CreatePanel();
	CreateComboBox();
}

void VPForms::VPFormAuditParameterCommand::CreateButton() {
	Button^ button_close = gcnew Button();
	button_close->Name = "close";
	button_close->Text = "Закрыть";
	button_close->Location = Drawing::Point(this->ClientSize.Width - 110, this->ClientSize.Height - 40);
	button_close->Size = Drawing::Size(100, 20);
	button_close->Anchor = AnchorStyles::Bottom | AnchorStyles::Right;
	button_close->Click += gcnew EventHandler(this, &VPFormAuditParameterCommand::OnClose);
	this->Controls->Add(button_close);

	Button^ button_path_input = gcnew Button();
	button_path_input->Name = "set_path_input";
	button_path_input->Text = "Обзор";
	button_path_input->Location = Drawing::Point(230, 60);
	button_path_input->Size = Drawing::Size(100, 20);
	button_path_input->Anchor = AnchorStyles::Top | AnchorStyles::Left;
	button_path_input->Click += gcnew EventHandler(this, &VPFormAuditParameterCommand::SetPathInput);
	this->Controls->Add(button_path_input);

	Button^ button_path_output = gcnew Button();
	button_path_output->Name = "set_path_output";
	button_path_output->Text = "Обзор";
	button_path_output->Location = Drawing::Point(230, 630);
	button_path_output->Size = Drawing::Size(100, 20);
	button_path_output->Anchor = AnchorStyles::Top | AnchorStyles::Left;
	button_path_output->Click += gcnew EventHandler(this, &VPFormAuditParameterCommand::SetPathOutput);
	this->Controls->Add(button_path_output);
}

void VPForms::VPFormAuditParameterCommand::CreateTextBox() {
	TextBox^ text_boxe_main = gcnew TextBox();
	text_boxe_main->Name = "main_text";
	text_boxe_main->Location = Drawing::Point(170, 120);
	text_boxe_main->Size = Drawing::Size(800, 500);
	text_boxe_main->Anchor = AnchorStyles::Top | AnchorStyles::Left;
	text_boxe_main->Multiline = true;
	this->Controls->Add(text_boxe_main);

	TextBox^ text_box_path_input = gcnew TextBox();
	text_box_path_input->Name = "get_path_config";
	text_box_path_input->Text = "Установть конфиг файл (/*.json)";
	text_box_path_input->Location = Drawing::Point(10, 60);
	text_box_path_input->Size = Drawing::Size(210, 20);
	text_box_path_input->Anchor = AnchorStyles::Top | AnchorStyles::Left;
	text_box_path_input->Multiline = false;
	this->Controls->Add(text_box_path_input);

	TextBox^ text_box_path_output = gcnew TextBox();
	text_box_path_output->Name = "get_path_output";
	text_box_path_output->Text = "Установть путь выгрузки (/*.html)";
	text_box_path_output->Location = Drawing::Point(10, 630);
	text_box_path_output->Size = Drawing::Size(210, 20);
	text_box_path_output->Anchor = AnchorStyles::Top | AnchorStyles::Left;
	text_box_path_output->Multiline = false;
	this->Controls->Add(text_box_path_output);
}

void VPForms::VPFormAuditParameterCommand::CreateLabel() {
	Label^ label_examination_select = gcnew Label();
	label_examination_select->Name = "info_examonation_select";
	label_examination_select->Text = "Выбрать метод провери:";
	label_examination_select->Location = Drawing::Point(10, 10);
	label_examination_select->AutoSize = true;
	label_examination_select->Anchor = AnchorStyles::Top | AnchorStyles::Left;
	this->Controls->Add(label_examination_select);

	Label^ label_select_categody = gcnew Label();
	label_select_categody->Name = "info_select_categody";
	label_select_categody->Text = "Выбрать категорию/IfcExportAs:";
	label_select_categody->Location = Drawing::Point(10, 90);
	label_select_categody->AutoSize = true;
	label_select_categody->Anchor = AnchorStyles::Top | AnchorStyles::Left;
	this->Controls->Add(label_select_categody);
}

void VPForms::VPFormAuditParameterCommand::CreatePanel() {
	Panel^ panel_contains_com_box= gcnew Panel();
	panel_contains_com_box->Name = "contains_com_box";
	panel_contains_com_box->Location = Drawing::Point(10, 120);
	panel_contains_com_box->Size = Drawing::Size(150, 500);
	panel_contains_com_box->Anchor = AnchorStyles::Top | AnchorStyles::Left;
	panel_contains_com_box->AutoScroll = true;
	panel_contains_com_box->BorderStyle = BorderStyle::FixedSingle;
	panel_contains_com_box->BackColor = Drawing::Color::FromArgb(208, 208, 208);
	this->Controls->Add(panel_contains_com_box);
}

void VPForms::VPFormAuditParameterCommand::CreateComboBox() {
	array<Object^>^ category = {
		"Категория",
		"IfcExportAs"
	};

	ComboBox^ combo_box_verific_method = gcnew ComboBox();
	combo_box_verific_method->Name = "verific_method";
	combo_box_verific_method->Location = Drawing::Point(10, 30);
	combo_box_verific_method->Size = Drawing::Size(100, 20);
	combo_box_verific_method->Anchor = AnchorStyles::Top | AnchorStyles::Left;
	combo_box_verific_method->Items->AddRange(category);
	combo_box_verific_method->DropDownWidth = category->Length * 20;
	combo_box_verific_method->DropDownWidth = 150;
	combo_box_verific_method->SelectedIndex = -1;
	combo_box_verific_method->SelectedIndexChanged += gcnew EventHandler(this, &VPFormAuditParameterCommand::SetCategory);
	combo_box_verific_method->DropDownStyle = ComboBoxStyle::DropDownList;	
	this->Controls->Add(combo_box_verific_method);
}

void VPForms::VPFormAuditParameterCommand::OnClose(Object^ sender, EventArgs^ e) {
	this->Close();
}

void VPForms::VPFormAuditParameterCommand::SetPathInput(Object^ sender, EventArgs^ e) {
	input_(this, EventArgs::Empty);
}

void VPForms::VPFormAuditParameterCommand::SetPathOutput(Object^ sender, EventArgs^ e) {
	output_(this, EventArgs::Empty);
}

void VPForms::VPFormAuditParameterCommand::SetCategory(Object^ sender, EventArgs^ e) {
	ComboBox^ combo_box = dynamic_cast<ComboBox^>(this->Controls["verific_method"]);
	verification_method_ = combo_box->Text;
	category_(this, EventArgs::Empty);
}

String^ VPForms::VPFormAuditParameterCommand::GetVerificationMethod() {
	return verification_method_;
}