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
	if(form_->GetVerificationMethod() == "IfcExportAs") {
		verification_method_ = VerificationMethod::IfcExportAs;
	} else {
		verification_method_ = VerificationMethod::Category;
	}
}

void Commands::AuditParameterCommand::SetParseJSON(Object^ sender, EventArgs^ e) {
	form_->ClearCheckBox();

	std::ifstream in(msclr::interop::marshal_as<std::string>(form_->GetPathInput()));
	json_reader::JsonReaderBase js_reader(in);
	int num_box = 1;

	for(const auto& data : js_reader.ParseDataElement()) {
		String^ id = gcnew String(data.id.c_str());
		String^ name = gcnew String(data.built_in_category.c_str());
		String^ text = gcnew String(data.name.c_str());
		
		List<String^>^ parameters = gcnew List<String^>();

		for(const auto& param : data.parameters) {
			parameters->Add(gcnew String(param.c_str()));
		}
		form_->CreateCheckBox(name, text, 
				gcnew Tuple<int, List<String^>^>(Convert::ToInt32(id), parameters), num_box);
		++num_box;
	}
}

void Commands::AuditParameterCommand::Audit(Object^ sender, EventArgs^ e) {

	Windows::Forms::Panel^ panel = dynamic_cast<Windows::Forms::Panel^>(form_->Controls["contains_com_box"]);

	category_base_element_ = gcnew Dictionary<String^, List<Elements::BaseElement^>^>();

	List<Tuple<String^, int, int>^>^ category_not_filled_no_parameter = gcnew List<Tuple<String^, int, int>^>();

	Windows::Forms::DataGridView^ table = dynamic_cast<Windows::Forms::DataGridView^>(form_->Controls["table_category"]);
	table->Rows->Clear();

	for each(Tuple<int, List<String^>^>^ data in form_->GetIdCategory()) {

		Services::BaseService^ base_service = gcnew Services::BaseService(doc_, data->Item1, data->Item2);
		List<Elements::BaseElement^>^ base_elements = nullptr;

		String^ category = nullptr;
		int no_filled = 0;
		int no_parameter = 0;

		for each(Elements::BaseElement^ element in base_service->GetElemenst()) {
			if(element->GetParameters() == nullptr) continue;
			
			if(base_elements == nullptr) {
				base_elements = gcnew List<Elements::BaseElement^>();
			}
			base_elements->Add(element);
			if(category->Empty) {
				category = element->GetCategory();
			}

			for each(KeyValuePair<String^, String^>^ param_value in element->GetParameters()) {
				if(param_value->Value == "Ошибка - параметер не заполнен!") {
					++no_filled;
				}
				if(param_value->Value == "Ошибка - Параметр отсутствует у семейства типа/экземаляра") {
					++no_parameter;
				}
			}
		}
		if(category != nullptr && base_elements != nullptr) {
			table->Rows->Add(category, no_filled, no_parameter);
			category_base_element_->Add(category, base_elements);
		}
	}
}

void Commands::AuditParameterCommand::GetResultAudit(Object^ sender, EventArgs^ e) {
	Export::AuditParameterHtmlExport^ exp = gcnew Export::AuditParameterHtmlExport(form_->GetPathOutput());
	exp->CompileFile(category_base_element_);
}
