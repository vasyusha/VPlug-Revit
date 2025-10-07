#pragma once

using namespace System;
using namespace System::Windows::Forms;
namespace VPForms {

public ref class BaseVPForm : public Form {
public:
	void OnClose(Object^ sender, EventArgs^ e);
};

}