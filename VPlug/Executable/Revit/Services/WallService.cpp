#include "../../../Headers/Revit/Services/WallService.h"

namespace Services {

WallService::WallService(Document^ doc) : BaseService(doc) {
}

bool BoxesIntersect(BoundingBoxXYZ^ a, BoundingBoxXYZ^ b) {
	if (a == nullptr || b == nullptr) return false;

	XYZ^ aMin = a->Min;
	XYZ^ aMax = a->Max;
	XYZ^ bMin = b->Min;
	XYZ^ bMax = b->Max;

	bool overlapX = (aMin->X <= bMax->X) && (aMax->X >= bMin->X);
	bool overlapY = (aMin->Y <= bMax->Y) && (aMax->Y >= bMin->Y);
	bool overlapZ = (aMin->Z <= bMax->Z) && (aMax->Z >= bMin->Z);

	return overlapX && overlapY && overlapZ;
}

int CountRealOpeningsForWall(Document^ doc, Wall^ wall) {
	/*Получили список проёмов*/
	IList<ElementId^>^ inserts = wall->FindInserts(
		true,
		true,
		false,
		false
	);
	
	/*Получаем рамку геометрии стены*/
	BoundingBoxXYZ^ wallBox = wall->BoundingBox[nullptr];
	if (wallBox == nullptr)
		return 0;

	int count = 0;
	
	/*Перебор проёмов*/
	for each (ElementId^ id in inserts) {
		/*Получаем элемент*/
		Element^ e = doc->GetElement(id);
		if (e == nullptr)
			continue;
		
		/*Получаем семейство*/
		FamilyInstance^ fi = dynamic_cast<FamilyInstance^>(e);
		if (fi == nullptr)
			continue;

		/*Получаем категорию семейства*/
		Category^ cat = fi->Category;
		if (cat == nullptr)
			continue;

		/*Фильтрация*/
		BuiltInCategory bic = safe_cast<BuiltInCategory>(cat->Id->IntegerValue);
		bool isOpeningFamily =
			bic == BuiltInCategory::OST_Windows ||
			bic == BuiltInCategory::OST_Doors ||
			bic == BuiltInCategory::OST_SWallRectOpening ||
			bic == BuiltInCategory::OST_GenericModel;
		if (!isOpeningFamily)
			continue;
		
		/*Создаём хост-стену для сверки*/
		Wall^ hostWall = dynamic_cast<Wall^>(fi->Host);
		if (hostWall == nullptr)
			continue;
		
		/*Получаем рамку геометрии проёма*/
		BoundingBoxXYZ^ boxIns = fi->BoundingBox[nullptr];
		if (boxIns == nullptr)
			continue;

		/*1) Окно хостится в ЭТОЙ же стене*/
		if (hostWall->Id == wall->Id) {
			if (BoxesIntersect(wallBox, boxIns))
				count++;
			continue;
		}

		/*Окно хостится в ДРУГОЙ стене – shadow-кейс*/
		BoundingBoxXYZ^ boxHost = hostWall->BoundingBox[nullptr];
		if (boxHost == nullptr)
			continue;

		/*Нормаль хост-стены*/
		XYZ^ n = hostWall->Orientation;

		/*Центры bbox хост-стены и проверяемой стены*/
		XYZ^ hostCenter = (boxHost->Min + boxHost->Max) * 0.5;
		XYZ^ wallCenter = (wallBox->Min + wallBox->Max) * 0.5;

		/*Проекции центров на нормаль*/
		double hostN = hostCenter->DotProduct(n);
		double wallN = wallCenter->DotProduct(n);

		/*Сдвигаем проверяемую стену в сторону хоста по нормали*/
		double dn = hostN - wallN;
		XYZ^ shift = n * dn;

		BoundingBoxXYZ^ movedWallBox = gcnew BoundingBoxXYZ();
		movedWallBox->Min = wallBox->Min + shift;
		movedWallBox->Max = wallBox->Max + shift;

		/*Проверяем, пересекается ли "пододвинутая" стена с окном*/
		if (!BoxesIntersect(movedWallBox, boxIns))
			continue;

		count++;
	}
	return count;
}

Elements::WallElement^ WallService::BuildWallElement(Document^ doc, Element^ e, IEnumerable<String^>^ requiredParams) {

	Elements::WallElement^ we = Services::BaseService::BuildBaseElement<Elements::WallElement^>(doc, e, requiredParams);

	Autodesk::Revit::DB::Wall^ wall = dynamic_cast<Autodesk::Revit::DB::Wall^>(e);

	we->HasOpening = wall->FindInserts(true, true, false, false)->Count > 0;

	we->CountOpening = CountRealOpeningsForWall(doc, wall);
	ForgeTypeId^ areaId = ParameterUtils::GetParameterTypeId(BuiltInParameter::HOST_AREA_COMPUTED);
	Parameter^ areaParam = wall->GetParameter(areaId);

	if (areaParam != nullptr && areaParam->HasValue) {
		double areaFt = areaParam->AsDouble();
		double areaM2 = UnitUtils::ConvertFromInternalUnits(areaFt, UnitTypeId::SquareMeters);
		we->Area = areaM2;
	} 
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