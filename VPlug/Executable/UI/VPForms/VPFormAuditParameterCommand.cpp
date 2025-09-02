#include "..\..\..\Headlines\UI\VPForms\VPFormAuditParameterCommand.h"

VPForms::VPFormAuditParameterCommand::VPFormAuditParameterCommand() {
	this->Name = "audit_parameter";
	this->Text = "Инструментарий";
	this->Location = Drawing::Point(2500, 2500);
	this->Size = Drawing::Size(1000, 750);
	this->FormBorderStyle = ::FormBorderStyle::FixedSingle;
	this->MinimizeBox = false;
}

void VPForms::VPFormAuditParameterCommand::CreateControls() {
	CreateButton();
	CreateTextBox();
	CreateLabel();
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
	button_path_input->Location = Drawing::Point(230, 630);
	button_path_input->Size = Drawing::Size(100, 20);
	button_path_input->Anchor = AnchorStyles::Top | AnchorStyles::Left;
	button_path_input->Click += gcnew EventHandler(this, &VPFormAuditParameterCommand::SetPathInput);
	this->Controls->Add(button_path_input);

	Button^ button_path_output = gcnew Button();
	button_path_output->Name = "set_path_output";
	button_path_output->Text = "Обзор";
	button_path_output->Location = Drawing::Point(230, 60);
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

void VPForms::VPFormAuditParameterCommand::OnClose(Object^ sender, EventArgs^ e) {
	this->Close();
}

void VPForms::VPFormAuditParameterCommand::SetPathInput(Object^ sender, EventArgs^ e) {

}

void VPForms::VPFormAuditParameterCommand::SetPathOutput(Object^ sender, EventArgs^ e) {

}