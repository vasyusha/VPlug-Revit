#include "../../Headers/Commands/AuditWallOpeningCommand.h"

namespace Commands {

String^ DataOpening::Name::get() {
	return name_;
}

void DataOpening::Name::set(String^ value) {
	name_ = value;
}

int DataOpening::Id::get() {
	return id_;
}

void DataOpening::Id::set(int value) {
	id_ = value;
}

String^ DataOpening::CategoryName::get() {
	return categoryName_;
}

void DataOpening::CategoryName::set(String^ value) {
	categoryName_ = value;
}

String^ AuditElementWall::Name::get() {
	return name_;	
}

void AuditElementWall::Name::set(String^ value) {
	name_ = value;
}

int AuditElementWall::Id::get() {
	return id_;
}

void AuditElementWall::Id::set(int value) {
	id_ = value;	
}

String^ AuditElementWall::CategoryName::get() {
	return categoryName_;
}

void AuditElementWall::CategoryName::set(String^ value) {
	categoryName_ = value;
}

double AuditElementWall::Area::get() {
	return area_;
}

void AuditElementWall::Area::set(double value) {
	area_ = value;
}

int AuditElementWall::CountOpening::get() {
	return countOpening_;
}

void AuditElementWall::CountOpening::set(int value) {
	countOpening_ = value;
}

IList<DataOpening^>^ AuditElementWall::DataOpenings::get() {
	return dataOpenings_;
}

void AuditElementWall::DataOpenings::set(IList<DataOpening^>^ value) {
	dataOpenings_ = value;
}

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

IList<DataOpening^>^ AuditTypeWallSummary::DataOpenings::get() {
	return dataOpenings_;
}

void AuditTypeWallSummary::DataOpenings::set(IList<DataOpening^>^ value) {
	dataOpenings_ = value;
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
	form_->ExportRequest += gcnew MyForm::AuditWallOpeningExportHandler(this, &AuditWallOpeningCommand::Export);
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
	dataElementWall_ = gcnew List<AuditElementWall^>();

	for each (Elements::WallElement^ we in wallElements) {

		AuditElementWall^ auditElementWall = gcnew AuditElementWall();	
		auditElementWall->Name = we->Name;
		auditElementWall->Id = we->Id;
		auditElementWall->CategoryName = we->CategoryName;
		auditElementWall->Area = we->Area;
		auditElementWall->CountOpening = we->CountOpening;

		if (!dataTypeWallSummary_->ContainsKey(we->Name)) {
			dataTypeWallSummary_->Add(we->Name, gcnew AuditTypeWallSummary());
		}
		
		dataTypeWallSummary_[we->Name]->Name = we->Name;
		++dataTypeWallSummary_[we->Name]->TotalWalls;
		dataTypeWallSummary_[we->Name]->TotalArea += we->Area;

		if (we->HasOpening) {
			dataTypeWallSummary_[we->Name]->TotalOpening += we->CountOpening;
			dataTypeWallSummary_[we->Name]->TotalAreaWallsWithOpenings += we->Area;

			for each (Elements::BaseElement^ be in we->LogicChildren) {
				DataOpening^ dataOpening = gcnew DataOpening();
				dataOpening->Name = be->Name;
				dataOpening->Id = be->Id;
				dataOpening->CategoryName = be->CategoryName;
			}

		} else {
			dataTypeWallSummary_[we->Name]->TotalAreaWallsWithoutOpenings += we->Area;
		}
	}
	FillTable();

	form_->MarkAuditFinished(true);
}

void AuditWallOpeningCommand::FillTable() {
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

void AuditWallOpeningCommand::ExportPrepareData(ExportHtml::WallOpening::ReportModel^ repModel) {
	for each (KeyValuePair<String^, AuditTypeWallSummary^> kvp in dataTypeWallSummary_) {
		ExportHtml::WallOpening::ReportTypeWall^ reportTypeWall = gcnew ExportHtml::WallOpening::ReportTypeWall();

		reportTypeWall->Name = kvp.Value->Name;
		reportTypeWall->TotalWalls = kvp.Value->TotalWalls;
		reportTypeWall->TotalArea = kvp.Value->TotalArea;
		reportTypeWall->TotalOpening = kvp.Value->TotalOpening;
		reportTypeWall->TotalAreaWallsWithOpenings = kvp.Value->TotalAreaWallsWithOpenings;
		reportTypeWall->TotalAreaWallsWithoutOpenings = kvp.Value->TotalAreaWallsWithoutOpenings;

		repModel->DataTypeWall->Add(reportTypeWall);
	}

	for each (AuditElementWall^ ew in dataElementWall_) {
		ExportHtml::WallOpening::ReportElementWall^ reportElementWall = gcnew ExportHtml::WallOpening::ReportElementWall();
		
		reportElementWall->Name = ew->Name;
		reportElementWall->Id = ew->Id;
		reportElementWall->CategoryName = ew->CategoryName;
		reportElementWall->Area = ew->Area;
		reportElementWall->CountOpening = ew->CountOpening;
		reportElementWall->DataOpenings = gcnew List<ExportHtml::WallOpening::DataOpening^>();
		for each (DataOpening^ dataOpening in ew->DataOpenings) {
			ExportHtml::WallOpening::DataOpening^ expDataOpening = gcnew ExportHtml::WallOpening::DataOpening();
			expDataOpening->Id = dataOpening->Id;
			expDataOpening->Name = dataOpening->Name;
			expDataOpening->CategoryName = dataOpening->CategoryName;
			reportElementWall->DataOpenings->Add(expDataOpening);
		}
		repModel->DataElementWall->Add(reportElementWall);
	}
}

void AuditWallOpeningCommand::Export(String^ path) {
	ExportHtml::WallOpening::ReportModel^ repModel = gcnew ExportHtml::WallOpening::ReportModel();

	repModel->FilePath = doc_->PathName;
	repModel->ProjectName = doc_->Title;
	repModel->DataTimeStr = System::DateTime::Now.ToString("yyyy-MM-dd HH:mm:ss", System::Globalization::CultureInfo::InvariantCulture);
	
	ExportPrepareData(repModel);

	ExportHtml::WallOpening::AuditWallOpeningExportHtml^ exp = gcnew ExportHtml::WallOpening::AuditWallOpeningExportHtml();
	exp->SaveHtmlToFile(repModel, path);

	form_->MarkAuditExportFinished(true);
}

}//namespace Commands