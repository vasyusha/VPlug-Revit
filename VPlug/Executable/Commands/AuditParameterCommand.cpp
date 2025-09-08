#include "..\..\Headlines\Commands\AuditParameterCommand.h"

Result Commands::AuditParameterCommand::Execute(ExternalCommandData^ command_data, 
	String^% message, ElementSet^ elements) {

	UIDocument^ ui_doc = command_data->Application->ActiveUIDocument;
	doc_ = ui_doc->Document;

	form_ = gcnew VPForms::VPFormAuditParameterCommand();

	form_->category_ += gcnew EventHandler(this, &AuditParameterCommand::SetParseConfigJSON);
	form_->input_ += gcnew EventHandler(this, &AuditParameterCommand::SetParseJSON);
	form_->output_ += gcnew EventHandler(this, &AuditParameterCommand::GetResultAudit);
	form_->audit_ += gcnew EventHandler(this, &AuditParameterCommand::Audit);	

	form_->ShowDialog();

	return Result::Succeeded;
}

void Commands::AuditParameterCommand::SetParseConfigJSON(Object^ sender, EventArgs^ e) {
	TaskDialog::Show("Test", form_->GetVerificationMethod());
	if(form_->GetVerificationMethod() == "IfcExportAs") {
		verification_method_ = VerificationMethod::IfcExportAs;
	} else {
		verification_method_ = VerificationMethod::Category;
	}
}

void Commands::AuditParameterCommand::SetParseJSON(Object^ sender, EventArgs^ e) {
	//!!!TEST!!!
	System::Windows::Forms::TextBox^ text_box = dynamic_cast<System::Windows::Forms::TextBox^>(form_->Controls["main_text"]);
	form_->ClearCheckBox();

	std::ifstream in(msclr::interop::marshal_as<std::string>(form_->GetPathInput()));
	json_reader::JsonReaderBase js_reader(in);
		text_box->Text += gcnew String("TESTs") + "\r\n";
	int num_box = 1;

	for(const auto& data : js_reader.ParseDataElement()) {
		text_box->Text += gcnew String("{") + "\r\n";
		String^ id = gcnew String(data.id.c_str());
		String^ name = gcnew String(data.built_in_category.c_str());
		String^ text = gcnew String(data.name.c_str());
		
		text_box->Text += id + " = [" + name + " : " + text + "]" +"\r\n";
		for(const auto& param : data.parameters) {
			text_box->Text += gcnew String(param.c_str());
		}
		text_box->Text += gcnew String("}") + "\r\n";
		form_->CreateCheckBox(name, text, Convert::ToInt32(id), num_box);
		++num_box;
	}
	//!!!TEST!!!
	TaskDialog::Show("Test2", form_->GetPathInput());
}

void Commands::AuditParameterCommand::Audit(Object^ sender, EventArgs^ e) {
	//!!!TESTs!!!
	Windows::Forms::Panel^ panel = dynamic_cast<Windows::Forms::Panel^>(form_->Controls["contains_com_box"]);
	System::Windows::Forms::TextBox^ text_box = dynamic_cast<System::Windows::Forms::TextBox^>(form_->Controls["main_text"]);
	text_box->Clear();
	for each(int i in form_->GetIdCategory()) {
		
		text_box->Text += "\r\n" + i + "\r\n";
	}
	//!!!TESTs!!!
	TaskDialog::Show("Test4", "AUDIT");
}

void Commands::AuditParameterCommand::GetResultAudit(Object^ sender, EventArgs^ e) {
	TaskDialog::Show("Test3", form_->GetPathOutput());
}
