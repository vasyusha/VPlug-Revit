#pragma once

using namespace System;
using namespace System::IO;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;

namespace VPForms {

public ref class VPFormAuditParameterCommand : public System::Windows::Forms::Form {
private:
	String^ verification_method_;
	String^ file_path_input_;
	String^ file_path_output_;
	List<int>^ id_category_;

public:
	VPFormAuditParameterCommand();
	void CreateControls();
	void CreateButton();
	void CreateTextBox();
	void CreateLabel();
	void CreatePanel();
	void CreateComboBox();
	void CreateCheckBox(String^ name, String^ text, int tag, int num_box);

	void ClearCheckBox();
	void CreateTable();

	void OnClose(Object^ sender, EventArgs^ e);
	void SetPathInput(Object^ sender, EventArgs^ e);
	void SetPathOutput(Object^ sender, EventArgs^ e);
	void SetCategory(Object^ sender, EventArgs^e);
	void SetAudit(Object^ sender, EventArgs^ e);

	String^ GetVerificationMethod();
	String^ GetPathInput();
	String^ GetPathOutput();
	List<int>^ GetIdCategory();

	event EventHandler^ input_;
	event EventHandler^ output_;
	event EventHandler^ category_;
	event EventHandler^ audit_;

};

}