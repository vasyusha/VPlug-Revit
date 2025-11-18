#include "../../Headers/Commands/AuditWallOpeningCommand.h"

namespace Commands {

AuditTypeWallSummary::AuditTypeWallSummary() {
	filters_ = gcnew Dictionary<String^, String^>();
}

String^ AuditTypeWallSummary::Name::get() {
	return name_;
}

void AuditTypeWallSummary::Name::set(String^ value) {
	name_ = value;
}

int AuditTypeWallSummary::TotalWalls::get() {
	return totalWalls_;
}

void AuditTypeWallSummary::TotalWalls::set(int value) {
	totalWalls_ = value;
}

double AuditTypeWallSummary::TotalArea::get() {
	return totalArea_;
}

void AuditTypeWallSummary::TotalArea::set(double value) {
	totalArea_ = value;
}

int AuditTypeWallSummary::TotalOpening::get() {
	return totalOpening_;
}

void AuditTypeWallSummary::TotalOpening::set(int value) {
	totalOpening_ = value;
}

double AuditTypeWallSummary::TotalAreaWallsWithOpenings::get() {
	return totalAreaWallsWithOpenings_;
}

void AuditTypeWallSummary::TotalAreaWallsWithOpenings::set(double value) {
	totalAreaWallsWithOpenings_ = value;
}

double AuditTypeWallSummary::TotalAreaWallsWithoutOpenings::get() {
	return totalAreaWallsWithoutOpenings_;
}

void AuditTypeWallSummary::TotalAreaWallsWithoutOpenings::set(double value) {
	totalAreaWallsWithoutOpenings_ = value;
}

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

	List<String^>^ findParam = gcnew List<String^>();
	for each (Tuple<int, String^, String^>^ te in numFilterValue) {
		filtersValue->Add(te->Item2, te->Item3);
		findParam->Add(te->Item2);
	}

	Services::WallService^ wallService = gcnew Services::WallService(doc_);

	List<Elements::WallElement^>^ wallElements = wallService->CollectByCategory(BuiltInCategory::OST_Walls, filtersValue, findParam);

	dataTypeWallSummary_ = gcnew Dictionary<String^, AuditTypeWallSummary^>();

	for each (Elements::WallElement^ we in wallElements) {
		if (!dataTypeWallSummary_->ContainsKey(we->Name)) {
			dataTypeWallSummary_->Add(we->Name, gcnew AuditTypeWallSummary());
		}
		
		dataTypeWallSummary_[we->Name]->Name = we->Name;
		++dataTypeWallSummary_[we->Name]->TotalWalls;
		dataTypeWallSummary_[we->Name]->TotalArea += we->Area;

		if (we->HasOpening) {
			dataTypeWallSummary_[we->Name]->TotalOpening += we->CountOpening;
			dataTypeWallSummary_[we->Name]->TotalAreaWallsWithOpenings += we->Area;
		} else {
			dataTypeWallSummary_[we->Name]->TotalAreaWallsWithoutOpenings += we->Area;
		}
	}
	
	for each (KeyValuePair<String^, AuditTypeWallSummary^> kvp in dataTypeWallSummary_) {
		form_->AddRowTable(
			kvp.Value->Name,
			kvp.Value->TotalWalls.ToString(),
			kvp.Value->TotalArea.ToString("F2"),
			kvp.Value->TotalAreaWallsWithOpenings.ToString("F2"),
			kvp.Value->TotalAreaWallsWithoutOpenings.ToString("F2"),
			kvp.Value->TotalOpening.ToString()
		);
	}
}

}//namespace Commands