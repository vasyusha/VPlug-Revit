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
	form_->ExportRequest += gcnew MyForm::AuditWallOpeningExportHandler(this, &AuditWallOpeningCommand::Export);
}

void AuditWallOpeningCommand::Audit(IDictionary<String^, String^>^ filters) {
	List<String^>^ findParam = gcnew List<String^>();
	//в финд парам закинуть ключи из фильтров, тем самым мы получим значение фильра у парам

	filters_ = gcnew Dictionary<String^, IList<String^>^>();	

	for each (KeyValuePair<String^, String^> kvp in filters) {
		filters_->Add(kvp.Key, PrepareFilterValue(kvp.Value));
		findParam->Add(kvp.Key);
	}

	Services::WallService^ wallService = gcnew Services::WallService(doc_);

	List<MyDomain::Elements::WallElement^>^ wallElements = wallService->CollectByCategory(BuiltInCategory::OST_Walls, filters_, findParam);
	
	AuditElement(wallElements);

	reportResult_ = gcnew MyDomain::AuditWallOpeningsReport::ResultReport();

	reportResult_->AuditResult = auditResult_;

	reportResult_->ProjectName = doc_->Title;
	reportResult_->DateTimeStr = System::DateTime::Now.ToString("yyyy-MM-dd HH:mm:ss", System::Globalization::CultureInfo::InvariantCulture);

	FillTable();

	form_->MarkAuditFinished(true);
}

void AuditWallOpeningCommand::AuditElement(List<MyDomain::Elements::WallElement^>^ wallElements) {
	//scopAuditWallElements_ = gcnew Dictionary<String^, List<MyDomain::Elements::AuditWallOpenings::AuditWallElement^>^>();
	
	scopAuditWallElements_ = gcnew Dictionary<List<MyDomain::Elements::AuditWallOpenings::Scop^>^,
		List<MyDomain::Elements::AuditWallOpenings::AuditWallElement^>^>();

	scopAuditWallGroups_ = gcnew Dictionary<List<MyDomain::Elements::AuditWallOpenings::Scop^>^,
		MyDomain::Elements::AuditWallOpenings::AuditWallGroup^>();

	auditResult_ = gcnew MyDomain::Elements::AuditWallOpenings::AuditResult();
	reportResult_ = gcnew MyDomain::AuditWallOpeningsReport::ResultReport();

	for each (MyDomain::Elements::WallElement^ wallElement in wallElements) {
	
		List<MyDomain::Elements::AuditWallOpenings::Scop^>^ scops = gcnew List<MyDomain::Elements::AuditWallOpenings::Scop^>();
		
		List<MyDomain::Elements::AuditWallOpenings::AuditOpening^>^ auditOpenings = gcnew List<MyDomain::Elements::AuditWallOpenings::AuditOpening^>();

		for each (MyDomain::Parameters::Parameter^ parameter in wallElement->Parameters) {
			if (parameter->Value != nullptr && filters_->ContainsKey(parameter->Name)) {
				if (filters_[parameter->Name]->Contains(parameter->Value)) {
					MyDomain::Elements::AuditWallOpenings::Scop^ scop = gcnew MyDomain::Elements::AuditWallOpenings::Scop();
					
					scop->name = parameter->Name;
					scop->value = parameter->Value;

					scops->Add(scop);
				}
			}
		}

		for each (MyDomain::Elements::Element^ opening in wallElement->LogicChildrenOpenings) {
			MyDomain::Elements::AuditWallOpenings::AuditOpening^ auditOpening = gcnew MyDomain::Elements::AuditWallOpenings::AuditOpening();
			auditOpening->Element = opening;
			auditOpenings->Add(auditOpening);
		}
			
		MyDomain::Elements::AuditWallOpenings::AuditWallElement^ auditElement = gcnew MyDomain::Elements::AuditWallOpenings::AuditWallElement();
		auditElement->WallElement = wallElement;
		auditElement->Scops = scops;
		auditElement->AuditOpenings = auditOpenings;		

		if (scopAuditWallElements_->ContainsKey(scops)) {
			scopAuditWallElements_[scops]->Add(auditElement);
		} else {
			List<MyDomain::Elements::AuditWallOpenings::AuditWallElement^>^ auditWallElements = gcnew List<MyDomain::Elements::AuditWallOpenings::AuditWallElement^>();
			auditWallElements->Add(auditElement);
	
			scopAuditWallElements_->Add(scops, auditWallElements);
		}
		CollectAuditGroup(auditElement);
		auditResult_->AuditWallElements->Add(auditElement);
	}
}

void AuditWallOpeningCommand::CollectAuditGroup(MyDomain::Elements::AuditWallOpenings::AuditWallElement^ auditElement) {

	if (!scopAuditWallGroups_->ContainsKey(auditElement->Scops)) {

		MyDomain::Elements::AuditWallOpenings::AuditWallGroup^ auditGroup = gcnew MyDomain::Elements::AuditWallOpenings::AuditWallGroup();
		auditGroup->AuditWallElements->Add(auditElement);
				
		scopAuditWallGroups_->Add(auditElement->Scops, auditGroup);

	} else {
		scopAuditWallGroups_[auditElement->Scops]->AuditWallElements->Add(auditElement);
	}

	//scopAuditWallGroups_[auditElement->Scops]->Scops->AddRange(auditElement->Scops);
	scopAuditWallGroups_[auditElement->Scops]->Scops = auditElement->Scops;

	if (scopAuditWallGroups_[auditElement->Scops]->AuditOpenings == nullptr) {
		scopAuditWallGroups_[auditElement->Scops]->AuditOpenings = gcnew List<MyDomain::Elements::AuditWallOpenings::AuditOpening^>();
	} 

	if (auditElement->AuditOpenings != nullptr) {
		scopAuditWallGroups_[auditElement->Scops]->AuditOpenings->AddRange(auditElement->AuditOpenings);
	}
	
	StringBuilder^ sb = gcnew StringBuilder();
	for each (MyDomain::Elements::AuditWallOpenings::Scop^ scop in auditElement->Scops) {
		sb->AppendLine(scop->name + " - " + scop->value);
	}

	scopAuditWallGroups_[auditElement->Scops]->Name = sb->ToString();

	++scopAuditWallGroups_[auditElement->Scops]->TotalWalls;
	scopAuditWallGroups_[auditElement->Scops]->TotalArea += auditElement->WallElement->Area;
	scopAuditWallGroups_[auditElement->Scops]->TotalOpenings += auditElement->WallElement->CountOpenings;
	
	if (auditElement->WallElement->HasOpening) {
		scopAuditWallGroups_[auditElement->Scops]->TotalAreaWallsWithOpenings += auditElement->WallElement->Area;
	} else {
		scopAuditWallGroups_[auditElement->Scops]->TotalAreaWallsWithoutOpenings += auditElement->WallElement->Area;
	}
	auditResult_->AuditWallGroups->Add(scopAuditWallGroups_[auditElement->Scops]);
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
	for each (KeyValuePair<List<MyDomain::Elements::AuditWallOpenings::Scop^>^, MyDomain::Elements::AuditWallOpenings::AuditWallGroup^> kvp in scopAuditWallGroups_) {
		TaskDialog::Show("Test", kvp.Key->Count.ToString() + " - ");
		form_->AddRowTable(
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

	
	ExportHtml::AuditWallOpeningExportHtml^ exp = gcnew ExportHtml::AuditWallOpeningExportHtml();
	exp->SaveHtmlToFile(reportResult_, path);

	form_->MarkAuditExportFinished(true);
}
}//namespace Commands