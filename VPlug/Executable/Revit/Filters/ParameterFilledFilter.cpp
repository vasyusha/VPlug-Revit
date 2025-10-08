#include "..\..\..\Headers\Revit\Filters\ParameterFilledFilter.h"

String^ Filters::ParameterFilledFilter::CheckParam(Document^ doc, Element^ element, String^ parameter, bool onlyMissing) {
		
	Parameter^ p = element->LookupParameter(parameter);

	if (p == nullptr) {
		ElementId^ typeId = element->GetTypeId();
		if (typeId != nullptr && typeId != ElementId::InvalidElementId) {
			Element^ elementType = doc->GetElement(typeId);
			if (elementType != nullptr) {
				p = elementType->LookupParameter(parameter);				
			}
		}
	}

	if (p == nullptr)
		return onlyMissing ? gcnew String("Ошибка - Параметр отсутствует у семейства типа/экземаляра") : nullptr;

	auto invariant = System::Globalization::CultureInfo::InvariantCulture;
		
	bool filled;
	if (!p->HasValue) filled = false;
	else if (p->StorageType == StorageType::String) {
		String^ s = p->AsString();
		filled = !String::IsNullOrWhiteSpace(s);
	}
	else filled = true;

	if (onlyMissing) return filled ? nullptr : gcnew String("Ошибка - параметер не заполнен!");

	switch (p->StorageType) {
		case StorageType::Double : {
			double v = p->AsDouble();
			return v.ToString("R", invariant);
		}
		case StorageType::Integer : {
			int v = p->AsInteger();
			return v.ToString(invariant);
		}
		case StorageType::String : {
			String^ s = p->AsString();
			return s != nullptr ? s->Trim() : nullptr;
		}
		case StorageType::ElementId : {
			int id = p->AsElementId()->IntegerValue;
			return id.ToString(invariant);
		}
		default : return nullptr;
	}
}