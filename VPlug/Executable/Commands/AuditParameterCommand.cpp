#include "..\..\Headers\Commands\AuditParameterCommand.h"

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
	TaskDialog::Show("method", method);
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
	Windows::Forms::TextBox^ text_box = dynamic_cast<Windows::Forms::TextBox^>(form_->Controls["main_text"]);



	if(verification_method_ == VerificationMethod::Category) {
	JsonReader::JsonReaderAuditParameter^ json_reader = gcnew JsonReader::JsonReaderAuditParameter();
	List<JsonReader::CategorySpec^>^ specs = gcnew List<JsonReader::CategorySpec^>();
		//specs = json_reader->LoadCategorySpecs(form_->GetPathInput());
	specs = JsonReader::JsonReaderAuditParameter::LoadCategorySpecs(form_->GetPathInput());

	for each(JsonReader::CategorySpec^ x in specs) {
		text_box->Text += x->Id + "\r\n";
		text_box->Text += x->Name + "\r\n";
		text_box->Text += x->BuiltInCategory + "\r\n";
		text_box->Text += "{" +  "\r\n";
		for each(String^ str in x->Parameters) {
			text_box->Text += str + "\r\n\n";
		}
		text_box->Text += "}" +  "\r\n";
	}

	} else if(verification_method_ == VerificationMethod::one_param) {
		List<JsonReader::UserFilterSpec^>^ specs = gcnew List<JsonReader::UserFilterSpec^>();
		specs = JsonReader::JsonReaderAuditParameter::LoadUserFilterSpec(form_->GetPathInput());
		
		for each(JsonReader::UserFilterSpec^ x in specs) {
			for each(JsonReader::Filter^ f in x->Filters) {
				text_box->Text += "Filter - { Имя: " + f->Name + " -> Значение: " + f->Value + " }\r\n"; 
			}
			text_box->Text += "{" +  "\r\n";
			for each(String^ str in x->Parameters) {
				text_box->Text += str + "\r\n\n";
			}
			text_box->Text += "}" +  "\r\n";
		}


	}

	/*
	std::ifstream in(msclr::interop::marshal_as<std::string>(form_->GetPathInput()));
	json_reader::JsonReaderAuditParameter js_reader(in);
	int num_box = 1;
	
	if(verification_method_ == VerificationMethod::Category) {
		js_reader.ParseCategory();
		TaskDialog::Show("Test", "SetParseJSON");
		category_ = gcnew Dictionary<int, CategoryFilter^>();

		for(const auto& data : js_reader.GetCategoryFilters()) {
			TaskDialog::Show("Test", gcnew String(data.name.c_str()));
			CategoryFilter^ category_filter = gcnew CategoryFilter();
			category_filter->id = Convert::ToInt32(gcnew String(data.id_category.c_str()));
			category_filter->name = gcnew String(data.name.c_str());
			category_filter->parameters = gcnew List<String^>();
			for(const auto& param : data.parameters) {
				category_filter->parameters->Add(gcnew String(param.c_str()));
			}
			category_->Add(num_box, category_filter);

			form_->CreateCheckBox(gcnew String(data.name.c_str()), gcnew String(data.name.c_str()), num_box);
			++num_box;
		}

	} else if(verification_method_ == VerificationMethod::one_param) {
		js_reader.ParseUniversal();

		universal_ = gcnew Dictionary<int, UniversalFilter^>();

		for(const auto& data : js_reader.GetUniversalFilters()) {
			UniversalFilter^ universal_filter = gcnew UniversalFilter();
			List<ParameterCheckFilter^>^ parameters_checks_filters = gcnew List<ParameterCheckFilter^>(); 
			
			for(const auto& filter : data.param_value_filter) {
				ParameterCheckFilter^ parameter_check_filter = gcnew ParameterCheckFilter();
				parameter_check_filter->name = gcnew String(filter.name.c_str());
				parameter_check_filter->expected_value = gcnew String(filter.expected_value.c_str());
				parameters_checks_filters->Add(parameter_check_filter);
			}
	
			List<String^>^ parameters = gcnew List<String^>();
			for(const auto& param : data.parameters) {
				parameters->Add(gcnew String(param.c_str()));
			}
			universal_filter->parameter_value_filter = parameters_checks_filters;
			universal_filter->parameters = parameters;

			universal_->Add(num_box, universal_filter);
			++num_box;
		}
	}
	*/
	/*
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
		for(const auto& data : js_reader.ParseUserParam()) {
			String^ user_filter_param = gcnew String(data.first.first.c_str());
			String^ user_filter_value = gcnew String(data.first.second.c_str());

			String^ name = user_filter_param + " : " + user_filter_value;
			String^ text = user_filter_param + " : " + user_filter_value;

			List<String^>^ parameters = gcnew List<String^>();

			for(const auto& param : data.second) {
				parameters->Add(gcnew String(param.c_str()));
			}
			Tuple<String^, String^>^ param_value = gcnew Tuple<String^, String^>(user_filter_param, user_filter_value);
			Tuple<Tuple<String^, String^>^, List<String^>^>^ tag = gcnew Tuple<Tuple<String^, String^>^, List<String^>^>(param_value, parameters);
			form_->CreateCheckBox(name
				, text
				, tag
				, num_box
			);

			++num_box;
		}
		*/
		/*
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
		*/
}

void Commands::AuditParameterCommand::Audit(Object^ sender, EventArgs^ e) {

	Windows::Forms::Panel^ panel = dynamic_cast<Windows::Forms::Panel^>(form_->Controls["contains_com_box"]);

	category_base_element_ = gcnew Dictionary<Tuple<String^, String^>^, List<Elements::BaseElement^>^>();

	List<Tuple<String^, int, int>^>^ category_not_filled_no_parameter = gcnew List<Tuple<String^, int, int>^>();

	Windows::Forms::DataGridView^ table = dynamic_cast<Windows::Forms::DataGridView^>(form_->Controls["table_category"]);
	table->Rows->Clear();

	for each(int id_num_box_active in form_->GetIdNumBoxActive()) {
		
		if(verification_method_ == VerificationMethod::Category) {
			CategoryFilter^ category_filter = gcnew CategoryFilter();
			category_->TryGetValue(id_num_box_active, category_filter);	
		
			Services::BaseService^ base_service = gcnew Services::BaseService(doc_, category_filter->id, category_filter->parameters);
			List<Elements::BaseElement^>^ base_elements = nullptr;

			String^ built_in_category = nullptr;
			String^ category_name = nullptr;
			int no_filled = 0;
			int no_parameter = 0;

			for each(Elements::BaseElement^ element in base_service->GetElemenst()) {
				if(element == nullptr) continue;
				if(base_elements == nullptr) {
					base_elements = gcnew List<Elements::BaseElement^>();
				}

				base_elements->Add(element);

				if(category_name == nullptr && built_in_category == nullptr) {
					category_name = element->GetCategoryName();
					built_in_category = element->GetBuiltInCategory();
				}

				for each(KeyValuePair<String^, String^>^ kvp in element->GetParameters()) {
					if(kvp->Value == "Ошибка - параметер не заполнен!") {
						++no_filled;
					}
					if(kvp->Value == "Ошибка - Параметр отсутствует у семейства типа/экземаляра") {
						++no_parameter;
					}
				}

				if(category_name != nullptr && base_elements != nullptr) {
					table->Rows->Add(category_name, no_filled, no_parameter);

					category_base_element_->Add(gcnew Tuple<String^, String^>(category_name, built_in_category), base_elements);
				}
			}
		} else if(verification_method_ == VerificationMethod::one_param) {

		}
	}

	/*
	if(verification_method_ == VerificationMethod::Category) {
	
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

	} else if(verification_method_ == VerificationMethod::one_param) {
		Windows::Forms::TextBox^ text_box = dynamic_cast<Windows::Forms::TextBox^>(form_->Controls["main_text"]);
		for each(Tuple<Tuple<String^, String^>^, List<String^>^>^ data in form_->GetUserParam()) {
			
			text_box->Text += "\r\n" + data->Item1->Item1 + " -> " + data->Item1->Item2;

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
				category_name = data->Item1->Item2;
				built_in_category = data->Item1->Item2;
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
	*/
}

void Commands::AuditParameterCommand::GetResultAudit(Object^ sender, EventArgs^ e) {
	Export::AuditParameterHtmlExport^ exp = gcnew Export::AuditParameterHtmlExport(form_->GetPathOutput());
	exp->CompileFile(category_base_element_);
}
