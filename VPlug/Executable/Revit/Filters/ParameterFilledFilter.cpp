#include "..\..\..\Headlines\Revit\Filters\ParameterFilledFilter.h"

String^ Filters::ParameterFilledFilter::CheckParam(Document^ doc, Element^ element, String^ parameter) {
	if(element == nullptr) return nullptr;

	Parameter^ find_parameter = element->LookupParameter(parameter);

	if(find_parameter == nullptr) {
		//!!!TESTs!!! тест конструкции
		try {
			Element^ element_type = doc->GetElement(element->GetTypeId());
			find_parameter = element_type->LookupParameter(parameter);

		} catch(...) { 
			//NullReferenceException - если элемент не имеет типа
			//InvalidOperationException - если тип недоступен или элемент не поддерживает типизацию
			//ArgumentException - если попытка получить тип у неверного объекта
		}
	}

	String^ value = nullptr;

	if(find_parameter != nullptr) {
		switch (find_parameter->StorageType) {
			case StorageType::Double :
				value = find_parameter->AsValueString();
				break;
			case StorageType::Integer : 
				value = find_parameter->AsInteger().ToString();
				break;
			case StorageType::String :
				value = find_parameter->AsString();
				break;
			case StorageType::ElementId :
				value = find_parameter->AsElementId()->IntegerValue.ToString();
				break;
			default:
				value = "Ошибка, неизвестный элемент";
				break;
		}
	}

	if(find_parameter != nullptr) {
		if(!find_parameter->HasValue) {
			value = "Ошибка - параметер не заполнен!";
		}
	} else {
		value = "Ошибка - Параметр отсутствует у семейства типа/экземаляра";
	}
	
	return value;
}