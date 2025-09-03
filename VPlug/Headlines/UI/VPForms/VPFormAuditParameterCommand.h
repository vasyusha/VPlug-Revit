#pragma once

using namespace System;
using namespace System::Windows::Forms;

namespace VPForms {

public ref class VPFormAuditParameterCommand : public System::Windows::Forms::Form {
public:
	VPFormAuditParameterCommand();
	void CreateControls();
	void CreateButton();
	void CreateTextBox();
	void CreateLabel();
	void CreatePanel();
	void CreateComboBox();

	void OnClose(Object^ sender, EventArgs^ e);
	void SetPathInput(Object^ sender, EventArgs^ e);
	void SetPathOutput(Object^ sender, EventArgs^ e);
	void SetCategory(Object^ sender, EventArgs^e);

	event EventHandler^ input_;
	event EventHandler^ output_;
	event EventHandler^ category_;

};

}