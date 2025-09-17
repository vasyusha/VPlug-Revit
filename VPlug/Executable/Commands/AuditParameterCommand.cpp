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
	String^ method = form_->GetVerificationMethod();

	if(method == "Категория") {
		verification_method_ = VerificationMethod::Category;
	} else if(method == "По 1 параметру") {
		verification_method_ = VerificationMethod::one_param;
	} else if(method == "По 2 параметрам") {
		verification_method_ = VerificationMethod::two_param;
	}
}

void Commands::AuditParameterCommand::SetParseJSON(Object^ sender, EventArgs^ e) {
	form_->ClearCheckBox();

	std::ifstream in(msclr::interop::marshal_as<std::string>(form_->GetPathInput()));
	json_reader::JsonReaderBase js_reader(in);
	int num_box = 1;

	if(verification_method_ == VerificationMethod::Category) {

	//Category
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

	} else if(verification_method_ == VerificationMethod::one_param) {

	//One param
		for(const auto& data : js_reader.ParseOneParam()) {
			String^ name = gcnew String(data.first.c_str());
			String^ text = gcnew String(data.first.c_str());

			List<String^>^ parameters = gcnew List<String^>();
		
			for(const auto& param : data.second) {
				parameters->Add(gcnew String(param.c_str()));
			}
			form_->CreateCheckBox(name, text, 
				gcnew Tuple<int, List<String^>^>(num_box, parameters), num_box);
			++num_box;
		} 
	
	} else if(verification_method_ == VerificationMethod::two_param) {
		
	//Two param
		for(const auto& data : js_reader.ParseTwoParam()) {
			String^ name = gcnew String(data.first.first.c_str()) + " - " + gcnew String(data.first.second.c_str());
			String^ text = gcnew String(data.first.first.c_str()) + " - " + gcnew String(data.first.second.c_str());

		List<String^>^ parameters = gcnew List<String^>();

		for(const auto& param : data.second) {
			parameters->Add(gcnew String(param.c_str()));
		}
			form_->CreateCheckBox(name, text, 
				gcnew Tuple<int, List<String^>^>(num_box, parameters), num_box);
			++num_box;
		}
	}
}

void Commands::AuditParameterCommand::Audit(Object^ sender, EventArgs^ e) {

	Windows::Forms::Panel^ panel = dynamic_cast<Windows::Forms::Panel^>(form_->Controls["contains_com_box"]);

	category_base_element_ = gcnew Dictionary<Tuple<String^, String^>^, List<Elements::BaseElement^>^>();

	List<Tuple<String^, int, int>^>^ category_not_filled_no_parameter = gcnew List<Tuple<String^, int, int>^>();

	Windows::Forms::DataGridView^ table = dynamic_cast<Windows::Forms::DataGridView^>(form_->Controls["table_category"]);
	table->Rows->Clear();

	for each(Tuple<int, List<String^>^>^ data in form_->GetIdCategory()) {

		Services::BaseService^ base_service = gcnew Services::BaseService(doc_, data->Item1, data->Item2);
		List<Elements::BaseElement^>^ base_elements = nullptr;

		String^ built_in_category = nullptr;
		String^ category_name = nullptr;
		int no_filled = 0;
		int no_parameter = 0;

		for each(Elements::BaseElement^ element in base_service->GetElemenst()) {
			if(element->GetParameters() == nullptr) continue;
			
			if(base_elements == nullptr) {
				base_elements = gcnew List<Elements::BaseElement^>();
			}
			base_elements->Add(element);
			if(category_name == nullptr && built_in_category == nullptr) {
				category_name = element->GetCategoryName();
				built_in_category = element->GetBuiltInCategory();
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
		if(category_name != nullptr && base_elements != nullptr) {
			table->Rows->Add(category_name, no_filled, no_parameter);
			category_base_element_->Add(gcnew Tuple<String^, String^>(category_name,
				built_in_category), base_elements);
		}
	}
}

void Commands::AuditParameterCommand::GetResultAudit(Object^ sender, EventArgs^ e) {
	Export::AuditParameterHtmlExport^ exp = gcnew Export::AuditParameterHtmlExport(form_->GetPathOutput());
	exp->CompileFile(category_base_element_);
}
