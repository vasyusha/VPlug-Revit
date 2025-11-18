#include "../../../Headers/Revit/Services/WallService.h"

namespace Services {

WallService::WallService(Document^ doc) : BaseService(doc) {
}

Elements::WallElement^ WallService::BuildWallElement(Document^ doc, Element^ e, IEnumerable<String^>^ requiredParams) {

	Elements::WallElement^ we = Services::BaseService::BuildBaseElement<Elements::WallElement^>(doc, e, requiredParams);

	Autodesk::Revit::DB::Wall^ wall = dynamic_cast<Autodesk::Revit::DB::Wall^>(e);


	we->HasOpening = wall->FindInserts(true, true, false, false)->Count > 0;
	
	IList<ElementId^>^ rawInstens = wall->FindInserts(true, true, false, false);

	int openingHosts = 0;
	int openingShadows = 0;
	for each (ElementId^ id in rawInstens) {
		Element^ ins = doc->GetElement(id);
		FamilyInstance^ fi = dynamic_cast<FamilyInstance^>(ins);
		if (fi != nullptr) {
			Wall^ hostWall = dynamic_cast<Wall^>(fi->Host);
			if (hostWall != nullptr && hostWall->Id == wall->Id) {
				++openingHosts;
			} else {
				++openingShadows;
			}
		} else {
			++openingShadows;
		}
	}

	we->CountOpening += openingHosts;
	we->CountOpening += openingShadows;

	/*
	if (we->HasOpening) {
		we->CountOpening = wall->FindInserts(true, true, false, false)->Count;
	}

	ForgeTypeId^ areaId = ParameterUtils::GetParameterTypeId(BuiltInParameter::HOST_AREA_COMPUTED);
	Parameter^ areaParam = wall->GetParameter(areaId);
	


	if (areaParam != nullptr && areaParam->HasValue) {
		double areaFt = areaParam->AsDouble();
		double areaM2 = UnitUtils::ConvertFromInternalUnits(areaFt, UnitTypeId::SquareMeters);
		we->Area = areaM2;

	} else {
		TaskDialog::Show("Area", "null");
	}
	*/

	return we;
}

List<Elements::WallElement^>^ WallService::CollectByCategory(
	BuiltInCategory bic,
	IDictionary<String^, String^>^ controlFilters,
	IEnumerable<String^>^ requiredParams) {

	auto result = gcnew List<Elements::WallElement^>();

	FilteredElementCollector^ col = gcnew FilteredElementCollector(doc_);
	col->OfCategory(bic);
	IList<Element^>^ elems = col->WhereElementIsNotElementType()->WhereElementIsViewIndependent()->ToElements();

	for each (Element ^ e in elems) {
		if (!MatchFilters(doc_, e, controlFilters)) continue;
		result->Add(BuildWallElement(doc_, e, requiredParams));
	}
	return result;
}




}//namespace Services