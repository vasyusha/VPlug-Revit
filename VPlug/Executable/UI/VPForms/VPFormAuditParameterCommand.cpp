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
	CreateTable();
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

	Button^ button_start_audit = gcnew Button();
	button_start_audit->Name = "start_audit";
	button_start_audit->Text = "Проверить";
	button_start_audit->Location = Drawing::Point(870, 60);
	button_start_audit->Size = Drawing::Size(100, 20);
	button_start_audit->Anchor = AnchorStyles::Top | AnchorStyles::Left;
	button_start_audit->Click += gcnew EventHandler(this, &VPFormAuditParameterCommand::SetAudit);
	button_start_audit->BackColor = Drawing::Color::Red;
	this->Controls->Add(button_start_audit);
}

void VPForms::VPFormAuditParameterCommand::CreateTextBox() {
	TextBox^ text_boxe_main = gcnew TextBox();
	text_boxe_main->Name = "main_text";
	text_boxe_main->Location = Drawing::Point(170, 120);
	text_boxe_main->Size = Drawing::Size(800, 200);
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

void VPForms::VPFormAuditParameterCommand::CreateCheckBox(String^ name, String^ text, Tuple<int, List<String^>^>^ id_param, int num_box) {
	Panel^ panel = dynamic_cast<Panel^>(this->Controls["contains_com_box"]);

	CheckBox^ check_box = gcnew CheckBox();
	check_box->Name = name;
	check_box->Text = text;
	check_box->Location = Drawing::Point(10, num_box * 20);
	check_box->AutoSize = true;
	check_box->Appearance = Appearance::Normal;
	check_box->AutoCheck = true;
	check_box->CheckedChanged += gcnew EventHandler(this, &VPFormAuditParameterCommand::CheckCheckBox);
	check_box->Tag = id_param;
	panel->Controls->Add(check_box);
}

void VPForms::VPFormAuditParameterCommand::ClearCheckBox() {
	this->Controls["contains_com_box"]->Controls->Clear();
}

void VPForms::VPFormAuditParameterCommand::CreateTable() {
	DataGridView^ table = gcnew DataGridView();
	table->Name = "table_category";
	table->Location = Drawing::Point(170, 340);
	table->Size = Drawing::Size(800, 280);
	table->Columns->Add("category", "Категория");
	table->Columns["category"]->Width = 250;
	table->Columns->Add("not_filled", "Не заполнено");
	table->Columns["not_filled"]->Width = 250;
	table->Columns->Add("no_parameter", "Нет параметра");
	table->Columns["no_parameter"]->Width = 250;
	this->Controls->Add(table);
}

void VPForms::VPFormAuditParameterCommand::OnClose(Object^ sender, EventArgs^ e) {
	this->Close();
}

void VPForms::VPFormAuditParameterCommand::SetPathInput(Object^ sender, EventArgs^ e) {
	if(!verification_method_) {
		MessageBox::Show("Установите метод проверки!", "Внимание", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return;
	}
	
	Stream^ my_stream;
	OpenFileDialog^ open_file_dialog = gcnew OpenFileDialog();
	open_file_dialog->Filter = "json files (*.json)|*.json";
	open_file_dialog->FilterIndex = 1;
	open_file_dialog->RestoreDirectory = true;

	if(open_file_dialog->ShowDialog() == ::DialogResult::OK) {
		if((my_stream = open_file_dialog->OpenFile()) != nullptr) {
		//MessageBox::Show(open_file_dialog->FileName, "Внимание", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			file_path_input_ = open_file_dialog->FileName;		
			my_stream->Close();
			this->Controls["get_path_config"]->Text = file_path_input_;
		}
	} else {
		return;
	}

	input_(this, EventArgs::Empty);
}

void VPForms::VPFormAuditParameterCommand::SetPathOutput(Object^ sender, EventArgs^ e) {
	if(!file_path_input_) {
		MessageBox::Show("Установите файл конфигурации!", "Внимание", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return;
	}
	if(start_audit_ == false) {
		MessageBox::Show("Установите элементы проверки!", "Внимание", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return;
	}
	if(compile_audit_ == false) {
		MessageBox::Show("Выполните проверку!", "Внимание", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return;
	}

	Stream^ my_stream;
	SaveFileDialog^ save_file_dialog = gcnew SaveFileDialog();
	save_file_dialog->Filter = "html files (*.html)| *.html";
	save_file_dialog->FilterIndex = 1;
	save_file_dialog->RestoreDirectory = true;

	if(save_file_dialog->ShowDialog() == ::DialogResult::OK) {
		if((my_stream = save_file_dialog->OpenFile()) != nullptr) {
			//MessageBox::Show(save_file_dialog->FileName, "Внимание", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			file_path_output_ = save_file_dialog->FileName;
			my_stream->Close();
			this->Controls["get_path_output"]->Text = file_path_input_;
		}
	} else {
		return;
	}
	output_(this, EventArgs::Empty);
}

void VPForms::VPFormAuditParameterCommand::SetCategory(Object^ sender, EventArgs^ e) {
	ComboBox^ combo_box = dynamic_cast<ComboBox^>(this->Controls["verific_method"]);
	verification_method_ = combo_box->Text;
	category_(this, EventArgs::Empty);
}

void VPForms::VPFormAuditParameterCommand::SetAudit(Object^ sender, EventArgs^ e) {
	if(start_audit_ == false) {
		MessageBox::Show("Установите элементы проверки!", "Внимание", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	}
	id_category_parameters_ = gcnew List<Tuple<int, List<String^>^>^>();

	for each(Control^ control in this->Controls["contains_com_box"]->Controls) {
		CheckBox^ check_box = dynamic_cast<CheckBox^>(control);
		if(check_box != nullptr && check_box->Checked) {
			Tuple<int, List<String^>^>^ tag = dynamic_cast<Tuple<int, List<String^>^>^>(check_box->Tag);
			id_category_parameters_->Add(
				gcnew Tuple<int, List<String^>^>(Convert::ToInt32(tag->Item1)
					, tag->Item2));
		}
	}
	audit_(this, EventArgs::Empty);
	compile_audit_ = true;
}

void VPForms::VPFormAuditParameterCommand::CheckCheckBox(Object^ sender, EventArgs^ e) {
	CheckBox^ check_box = safe_cast<CheckBox^>(sender);
	static int flag = 0;
	
	if(check_box->Checked) {
		++flag;
	} else {
		--flag;
	}
	if(flag > 0) {
		this->Controls["start_audit"]->BackColor = Drawing::Color::Green;
		start_audit_ = true;
	} else {
		this->Controls["start_audit"]->BackColor = Drawing::Color::Red;
		start_audit_ = false;
	}
	
}


String^ VPForms::VPFormAuditParameterCommand::GetVerificationMethod() {
	return verification_method_;
}

String^ VPForms::VPFormAuditParameterCommand::GetPathInput() {
	return file_path_input_;
}

String^ VPForms::VPFormAuditParameterCommand::GetPathOutput() {
	return file_path_output_;
}

List<Tuple<int, List<String^>^>^>^ VPForms::VPFormAuditParameterCommand::GetIdCategory() {
	return id_category_parameters_;
}