#include "../../../Headers/UI/MyForms/FormAuditParameter.h"

namespace MyForm {

FormAuditParameter::FormAuditParameter() {
	this->Text = "Проверка параметров";
	this->StartPosition = FormStartPosition::CenterScreen;
	this->Size = Drawing::Size(1000, 700);

}

void FormAuditParameter::BuildUi() {
	this->SuspendLayout();
	

	this->ResumeLayout(false);
}

}//namespace MyForm