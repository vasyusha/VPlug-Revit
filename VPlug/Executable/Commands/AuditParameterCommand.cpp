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
	if(method == "Категория") {
		verification_method_ = VerificationMethod::Category;
	} else if(method == "Фильтер") {
		verification_method_ = VerificationMethod::Filter;
	} 
}

void Commands::AuditParameterCommand::SetParseJSON(Object^ sender, EventArgs^ e) {
	form_->ClearCheckBox();
	Windows::Forms::TextBox^ text_box = dynamic_cast<Windows::Forms::TextBox^>(form_->Controls["main_text"]);

	int num_box = 1;

	if(verification_method_ == VerificationMethod::Category) {

		List<JsonReader::CategorySpec^>^ specs = JsonReader::JsonReaderAuditParameter::LoadCategorySpecs(form_->GetPathInput());

		for each(JsonReader::CategorySpec^ item in specs) {
			form_->CreateCheckBox(item->Id.ToString(), item->Name, item, num_box);
			++num_box;
		}

	} else if(verification_method_ == VerificationMethod::Filter) {

		List<JsonReader::UserFilterSpec^>^ specs = JsonReader::JsonReaderAuditParameter::LoadUserFilterSpec(form_->GetPathInput());

		for each(JsonReader::UserFilterSpec^ item in specs) {
			form_->CreateCheckBox(num_box.ToString(), item->Name, item, num_box);
			++num_box;
		}
	}

	text_box->Text += "Загружена конфигурация из файла: " + form_->GetPathInput(); 
}

void Commands::AuditParameterCommand::Audit(Object^ sender, EventArgs^ e) {

	Windows::Forms::Panel^ panel = dynamic_cast<Windows::Forms::Panel^>(form_->Controls["contains_com_box"]);
	DataGridView^ table = dynamic_cast<DataGridView^>(form_->Controls["table_category"]);

	category_base_element_ = gcnew Dictionary<Tuple<String^, String^>^, List<Elements::BaseElement^>^>();

	List<Tuple<String^, int, int>^>^ category_not_filled_no_parameter = gcnew List<Tuple<String^, int, int>^>();

	table->Rows->Clear();

	if (verification_method_ == VerificationMethod::Category) {

		for each (Windows::Forms::Control^ control in panel->Controls) {
			CheckBox^ checkBox = dynamic_cast<CheckBox^>(control);
			if (checkBox == nullptr || !checkBox->Checked) continue;

			JsonReader::CategorySpec^ spec = dynamic_cast<JsonReader::CategorySpec^>(checkBox->Tag);
			if(spec == nullptr) continue;

			Services::BaseService^ baseService = gcnew Services::BaseService(doc_, spec->Id, spec->Parameters);
			if (baseService == nullptr || baseService->GetElemenst() == nullptr) continue;

			List<Elements::BaseElement^>^ baseElements = gcnew List<Elements::BaseElement^>();
			String^ builtInCategory = nullptr;
			String^ categoryName = nullptr;
			int noFilled = 0;
			int noParameter = 0;

			for each (Elements::BaseElement^ element in baseService->GetElemenst()) {
				if (element->GetParameters() == nullptr) continue;

				if (builtInCategory == nullptr && categoryName == nullptr) {
					builtInCategory = element->GetBuiltInCategory();
					categoryName = element->GetCategoryName();
				}

				for each (KeyValuePair<String^, String^>^ kvp in element->GetParameters()) {
					if(kvp->Value == "Ошибка - параметер не заполнен!") ++noFilled;
					if(kvp->Value == "Ошибка - Параметр отсутствует у семейства типа/экземаляра") ++noParameter;

				}

				baseElements->Add(element);
			}
			if (builtInCategory != nullptr && categoryName != nullptr) {
				table->Rows->Add(categoryName, noFilled, noParameter);
				category_base_element_->Add(gcnew Tuple<String^, String^>(categoryName, builtInCategory), baseElements);
			}
		}
	} else if (verification_method_ == VerificationMethod::Filter) {
		
		for each (Windows::Forms::Control^ control in panel->Controls) {
			CheckBox^ checkBox = dynamic_cast<CheckBox^>(control);
			if (checkBox == nullptr || !checkBox->Checked) continue;

			JsonReader::UserFilterSpec^ spec = dynamic_cast<JsonReader::UserFilterSpec^>(checkBox->Tag);
			if(spec == nullptr) continue;

			Dictionary<String^, String^>^ controlParValue = gcnew Dictionary<String^, String^>();
			for each (JsonReader::Filter^ f in spec->Filters) {
				controlParValue->Add(f->Name, f->Value);
			}

			Services::BaseService^ baseService = gcnew Services::BaseService(doc_, controlParValue, spec->Parameters);
			if (baseService == nullptr || baseService->GetElemenst() == nullptr) continue;

			List<Elements::BaseElement^>^ baseElements = gcnew List<Elements::BaseElement^>();
			String^ builtInCategory = nullptr;
			String^ name = nullptr;
			int noFilled = 0;
			int noParameter = 0;

			for each (Elements::BaseElement^ element in baseService->GetElemenst()) {
				if (element->GetParameters() == nullptr) continue;

				if (builtInCategory == nullptr && name == nullptr) {
					builtInCategory = element->GetBuiltInCategory();
					name = spec->Name;
				}

				for each (KeyValuePair<String^, String^>^ kvp in element->GetParameters()) {
					if(kvp->Value == "Ошибка - параметер не заполнен!") ++noFilled;
					if(kvp->Value == "Ошибка - Параметр отсутствует у семейства типа/экземаляра") ++noParameter;

				}

				baseElements->Add(element);
			}
			if (builtInCategory != nullptr && name != nullptr) {
				table->Rows->Add(name, noFilled, noParameter);
				category_base_element_->Add(gcnew Tuple<String^, String^>(name, builtInCategory), baseElements);
			}
		}
	}
}

void Commands::AuditParameterCommand::GetResultAudit(Object^ sender, EventArgs^ e) {
	Export::AuditParameterHtmlExport^ exp = gcnew Export::AuditParameterHtmlExport(form_->GetPathOutput());
	exp->CompileFile(category_base_element_);
}
