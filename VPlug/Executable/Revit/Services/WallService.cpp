#include "../../../Headers/Revit/Services/WallService.h"

namespace Services {

WallService::WallService(Document^ doc) : BaseService(doc) {
}

Elements::WallElement^ WallService::BuildWallElement(Document^ doc, Element^ e, IEnumerable<String^>^ requiredParams) {
	auto we = gcnew Elements::WallElement();

	we->Id = e->Id->IntegerValue;
	we->UniqueId = e->UniqueId;
	we->Name = e->Name;

	Category^ cat = e->Category;
	if (cat != nullptr) {
		we->CategoryName = cat->Name;

		BuiltInCategory bic = static_cast<BuiltInCategory>(cat->Id->IntegerValue);
		we->BuiltInCategory = (int)bic;
		we->BuiltInCategoryName = bic.ToString();
	}

	if (requiredParams != nullptr) {
		for each (String^ pname in requiredParams) {
			Parameter^ p = TryGetParam(doc, e, pname);
			bool filled = IsFilled(p);
			Elements::ParamState stage;
			String^ val = nullptr;

			if (p == nullptr) {
				stage = Elements::ParamState::MissingParam;
			} else if (!filled) {
				stage = Elements::ParamState::EmptyValue;
			} else {
				stage = Elements::ParamState::Ok;
				val = ReadParamValue(p);
				if (String::IsNullOrEmpty(val)) stage = Elements::ParamState::EmptyValue;
			}
			we->AddParameter(pname, val, filled, stage);
		}
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