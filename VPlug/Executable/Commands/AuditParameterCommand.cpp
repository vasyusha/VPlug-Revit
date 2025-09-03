#include "..\..\Headlines\Commands\AuditParameterCommand.h"

Result Commands::AuditParameterCommand::Execute(ExternalCommandData^ command_data, 
	String^% message, ElementSet^ elements) {

	UIDocument^ ui_doc = command_data->Application->ActiveUIDocument;
	doc_ = ui_doc->Document;

	form_ = gcnew VPForms::VPFormAuditParameterCommand();
	form_->ShowDialog();

	return Result::Succeeded;
}