#include "../../Headers/Commands/AuditWallOpeningCommand.h"

namespace Commands {

Result AuditWallOpeningCommand::Execute(ExternalCommandData^ commandData,
	String^% message, ElementSet^ elements) {

	UIDocument^ uiDoc = commandData->Application->ActiveUIDocument;
	doc_ = uiDoc->Document;
	
	form_ = gcnew MyForm::FormAuditWallOpening();
	
	form_->ShowDialog();

	return Result::Succeeded;
}

}//namespace Commands