#pragma once

using namespace System;
using namespace System::Windows::Forms;

namespace VPForms {

public ref class VPFormAuditParameterCommand : Form {
public:
	VPFormAuditParameterCommand();
	void CreateControls();
	void CreateButton();
	void CreateTextBox();
	void CreateLabel();

	void OnClose(Object^ sender, EventArgs^ e);
	void SetPathInput(Object^ sender, EventArgs^ e);
	void SetPathOutput(Object^ sender, EventArgs^ e);
};

}