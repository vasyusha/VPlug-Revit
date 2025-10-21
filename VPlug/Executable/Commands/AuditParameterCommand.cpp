#include "../../Headers/Commands/AuditParameterCommand.h"

namespace Commands {

	Result AuditParameterCommand::Execute(ExternalCommandData^ commandData,
		String^% message, ElementSet^ elements) {

		UIDocument^ uiDoc = commandData->Application->ActiveUIDocument;
		doc_ = uiDoc->Document;
		
		form_ = gcnew MyForm::FormAuditParameter();

		form_->ShowDialog();

		return Result::Succeeded;
	}
}