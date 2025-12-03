#include "../../Headers/Commands/AuditWallOpeningCommand.h"

namespace Commands {

Result AuditWallOpeningCommand::Execute(ExternalCommandData^ commandData,
	String^% message, ElementSet^ elements) {
/*
	UIDocument^ uiDoc = commandData->Application->ActiveUIDocument;
	doc_ = uiDoc->Document;
	
	form_ = gcnew MyForm::FormAuditWallOpening();
	report = gcnew MyDomain::WallOpening::WallOpeningReport();
	SubscriptionEvent();
	
	form_->ShowDialog();
*/
	return Result::Succeeded;
}
/*
void AuditWallOpeningCommand::SubscriptionEvent() {
	form_->RunRequest += gcnew MyForm::AuditWallOpeningRunningHandler(this, &AuditWallOpeningCommand::Audit);
	form_->ExportRequest += gcnew MyForm::AuditWallOpeningExportHandler(this, &AuditWallOpeningCommand::Export);
}

void AuditWallOpeningCommand::PrepareElement(Elements::WallElement^ wallElement) {
	MyDomain::WallOpening::WallElementInfo^ wallElementInfo = gcnew MyDomain::WallOpening::WallElementInfo();
	
	wallElementInfo->Id = wallElement->Id;
	wallElementInfo->Name = wallElement->Name;
	wallElementInfo->CategoryName = wallElement->CategoryName;
	wallElementInfo->Area = wallElement->Area;
	wallElementInfo->CountOpenings = wallElement->CountOpening;

	for each (Elements::BaseElement^ baseElement in wallElement->LogicChildren) {
		MyDomain::WallOpening::OpeningInfo^ openingInfo = gcnew MyDomain::WallOpening::OpeningInfo();

		openingInfo->Id = baseElement->Id;
		openingInfo->Name = baseElement->Name;
		openingInfo->CategoryName = baseElement->CategoryName;

		wallElementInfo->Openings->Add(openingInfo);
	}
	report->WallElemnts->Add(wallElementInfo);
}

void AuditWallOpeningCommand::PrepareType(Elements::WallElement^ wallElement) {
	if (!report->WallTypes->ContainsKey(wallElement->Name)) {
		MyDomain::WallOpening::WallTypeInfo^ wallTypeInfo = gcnew MyDomain::WallOpening::WallTypeInfo();
		
		report->WallTypes->Add(wallElement->Name, wallTypeInfo);
	}
	
	report->WallTypes[wallElement->Name]->Name = wallElement->Name;
	++report->WallTypes[wallElement->Name]->TotalWalls;
	report->WallTypes[wallElement->Name]->TotalArea += wallElement->Area;

	if (wallElement->HasOpening) {
		report->WallTypes[wallElement->Name]->TotalOpenings += wallElement->CountOpening;
		report->WallTypes[wallElement->Name]->TotalAreaWallsWithOpenings += wallElement->Area;

		for each(Elements::BaseElement^ baseElement in wallElement->LogicChildren) {
			MyDomain::WallOpening::OpeningInfo^ openingInfo = gcnew MyDomain::WallOpening::OpeningInfo();

			openingInfo->Id = baseElement->Id;
			openingInfo->Name = baseElement->Name;
			openingInfo->CategoryName = baseElement->CategoryName;
			
			report->WallTypes[wallElement->Name]->Openings->Add(openingInfo);
		}
	} else {
		report->WallTypes[wallElement->Name]->TotalAreaWallsWithoutOpenings += wallElement->Area;
	}
}

void AuditWallOpeningCommand::Audit(IDictionary<String^, String^>^ filters) {
	Dictionary<String^, String^>^ filtersValue = gcnew Dictionary<String^, String^>();

	List<String^>^ findParam = gcnew List<String^>();

	Dictionary<String^, IList<String^>^>^ prepareFilters = gcnew Dictionary<String^, IList<String^>^>();	

	for each (KeyValuePair<String^, String^> kvp in filters) {
		prepareFilters->Add(kvp.Key, PrepareFilterValue(kvp.Value));
	}

	Services::WallService^ wallService = gcnew Services::WallService(doc_);

	List<Elements::WallElement^>^ wallElements = wallService->CollectByCategory(BuiltInCategory::OST_Walls, prepareFilters, findParam);

	for each (Elements::WallElement^ wallElement in wallElements) {
		PrepareElement(wallElement);
		PrepareType(wallElement);
	}

	FillTable();

	form_->MarkAuditFinished(true);
}

List<String^>^ AuditWallOpeningCommand::PrepareFilterValue(String^ value) {
	List<String^>^ result = gcnew List<String^>();

	if (String::IsNullOrEmpty(value)) return result;

	if (value[0] == '(') {
		String^ buffer = "";

		for each (Char cr in value) {
			if (cr == '(') continue;
			if (cr == ')') {
				if (!String::IsNullOrEmpty(buffer)) {
					result->Add(buffer);
				}
				buffer = "";
				continue;
			}
			if (cr == '|') {
				if (!String::IsNullOrEmpty(buffer)) {
					result->Add(buffer);
				}
				buffer = "";
				continue;
			}
			buffer += cr;
		}
	} else {
		result->Add(value);
	}
	return result;
}

void AuditWallOpeningCommand::FillTable() {
	for each (KeyValuePair<String^, MyDomain::WallOpening::WallTypeInfo^> kvp in report->WallTypes) {
		form_->AddRowTable (
			kvp.Value->Name,
			kvp.Value->TotalWalls.ToString(),
			kvp.Value->TotalArea.ToString("F3"),
			kvp.Value->TotalAreaWallsWithOpenings.ToString("F3"),
			kvp.Value->TotalAreaWallsWithoutOpenings.ToString("F3"),
			kvp.Value->TotalOpenings.ToString()
		);
	}
}

void AuditWallOpeningCommand::Export(String^ path) {

	report->ProjectName = doc_->Title;
	report->DateTimeStr = System::DateTime::Now.ToString("yyyy-MM-dd HH:mm:ss", System::Globalization::CultureInfo::InvariantCulture);
	
	ExportHtml::AuditWallOpeningExportHtml^ exp = gcnew ExportHtml::AuditWallOpeningExportHtml();
	exp->SaveHtmlToFile(report, path);

	form_->MarkAuditExportFinished(true);
}
*/
}//namespace Commands