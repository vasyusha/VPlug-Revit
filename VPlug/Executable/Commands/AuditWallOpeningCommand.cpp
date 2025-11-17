#include "../../Headers/Commands/AuditWallOpeningCommand.h"

namespace Commands {

Result AuditWallOpeningCommand::Execute(ExternalCommandData^ commandData,
	String^% message, ElementSet^ elements) {

	UIDocument^ uiDoc = commandData->Application->ActiveUIDocument;
	doc_ = uiDoc->Document;
	
	form_ = gcnew MyForm::FormAuditWallOpening();

	SubscriptionEvent();
	
	form_->ShowDialog();

	return Result::Succeeded;
}

void AuditWallOpeningCommand::SubscriptionEvent() {
	form_->RunRequest += gcnew MyForm::AuditWallOpeningRunningHandler(this, &AuditWallOpeningCommand::Audit);
}

void AuditWallOpeningCommand::Audit(List<Tuple<int, String^, String^>^>^ numFilterValue) {
	Dictionary<String^, String^>^ filtersValue = gcnew Dictionary<String^, String^>();

	for each (Tuple<int, String^, String^>^ te in numFilterValue) {
		filtersValue->Add(te->Item2, te->Item3);
	}

	List<String^>^ findParam = gcnew List<String^>();
	findParam->Add("Площадь");
	Services::WallService^ wallService = gcnew Services::WallService(doc_);

	List<Elements::WallElement^>^ wallElements = wallService->CollectByCategory(BuiltInCategory::OST_Walls, filtersValue, findParam);

	for each(Elements::WallElement^ we in wallElements) {
		form_->AddRowTable(we->Name);
	}

}

}//namespace Commands