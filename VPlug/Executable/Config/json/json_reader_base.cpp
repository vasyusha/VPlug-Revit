#include "..\..\..\Headlines\Config\json\json_reader_base.h"

json_reader::JsonReaderBase::JsonReaderBase(std::istream& input)
	: document_(json::Load(input)) {
}

std::map<std::string, std::string> json_reader::JsonReaderBase::ParseMapStringString() {
	std::map<std::string, std::string> result;
	
	if(document_.GetRoot().IsDict()) {
		for(const auto& [key, value] : document_.GetRoot().AsDict()) {
			if(value.IsString()) {
				result.emplace(key, value.AsString());
			}
		}
	}
	return result;
}

std::map<std::string, std::vector<std::string>> json_reader::JsonReaderBase::ParseMapStringVectorString() {
	std::map<std::string, std::vector<std::string>> result;
	
	if(document_.GetRoot().IsDict()) {
		for(const auto& [key, value] : document_.GetRoot().AsDict()) {
			if(value.IsArray()) {
				for(const auto& str : value.AsArray()) {
					if(str.IsString()) {
						result[key].push_back(str.AsString());
					}
				}
			}
		}
	}
	return result;
}

std::map<std::string, std::map<std::string, std::string>> json_reader::JsonReaderBase::ParseMapStringMapStringString() {
	std::map<std::string, std::map<std::string, std::string>> result;
	
	if(document_.GetRoot().IsDict()) {
		for(const auto& [key, value] : document_.GetRoot().AsDict()) {
			if(value.IsDict()) {
				std::map<std::string, std::string> data;
				for(const auto& [key2, value2] : value.AsDict()) {
					if(value2.IsString()) {
						data[key2] = value2.AsString();
					}
				}
				result.emplace(std::make_pair(key, data));
			}
		}
	}
	return result;
}

std::map<std::pair<std::string, std::string>, std::vector<std::string>> json_reader::JsonReaderBase::ParseMapPairStringStringVectorString() {
	std::map<std::pair<std::string, std::string>, std::vector<std::string>> result;

	if(document_.GetRoot().IsArray()) {
		for(const auto& cont : document_.GetRoot().AsArray()) {
			if(cont.IsDict() && cont.AsDict().size() == 2) {
				json::Node it_key;
				json::Node it_value;
				try {
					it_key = cont.AsDict().at("key");
					it_value = cont.AsDict().at("value");
				} catch (std::out_of_range) {
					return result;
				}
				std::vector<std::string> data;

				for(const auto& value : it_value.AsArray()) {
					data.push_back(value.AsString());
				}
				result[std::make_pair(it_key.AsArray()[0].AsString(), it_key.AsArray()[1].AsString())] = data;
			}
		}
	}
	return result;
}

std::vector<std::map<std::string, std::string>> json_reader::JsonReaderBase::ParseVectorMapStringString() {
	std::vector<std::map<std::string, std::string>> result;

	if(document_.GetRoot().IsArray()) {
		for(const auto& cont : document_.GetRoot().AsArray()) {
			if(cont.IsDict() && cont.AsDict().size() == 3) {
				json::Node it_Id;
				json::Node it_BuiltInCategory;
				json::Node it_Name;
				try {
					it_Id= cont.AsDict().at("Id");
					it_BuiltInCategory= cont.AsDict().at("BuiltInCategory");
					it_Name = cont.AsDict().at("Name");
				} catch (std::out_of_range) {
					return result;
				}
				std::map<std::string, std::string> data;
				for(const auto& [key, value] : cont.AsDict()) {
					data.emplace(std::make_pair(key, value.AsString()));	
				}
				result.push_back(data);
			}
		}
	}
	return result;
}

std::vector<json_reader::JsonReaderBase::DataElement> json_reader::JsonReaderBase::ParseDataElement() {
	std::vector<DataElement> result;

	if(document_.GetRoot().IsArray()) {
		for(const auto& cont : document_.GetRoot().AsArray()) {
			DataElement data_element;
			if(cont.IsDict() && cont.AsDict().size() == 4) {
				json::Node it_Id;
				json::Node it_BuiltInCategory;
				json::Node it_Name;
				json::Node it_Parameters;
				try {
					it_Id= cont.AsDict().at("Id");
					it_BuiltInCategory= cont.AsDict().at("BuiltInCategory");
					it_Name = cont.AsDict().at("Name");
					it_Parameters = cont.AsDict().at("Parameters");
				} catch (std::out_of_range) {
					return result;
				}
				data_element.id = it_Id.AsString();
				data_element.built_in_category = it_BuiltInCategory.AsString();
				data_element.name = it_Name.AsString();

				for(const auto& value : it_Parameters.AsArray()) {
					data_element.parameters.push_back(value.AsString());
				}
				result.push_back(data_element);
			}
		}
	}
	return result;
}

std::map<std::string, std::vector<std::string>> json_reader::JsonReaderBase::ParseOneParam() {
	std::map<std::string, std::vector<std::string>> result;

	if(document_.GetRoot().IsArray()) {
		for(const auto& cont : document_.GetRoot().AsArray()) {
			if(cont.IsDict() && cont.AsDict().size() == 2) {
				json::Node it_user_param;
				json::Node it_parameters;
				try {
					it_user_param = cont.AsDict().at("key");
					it_parameters = cont.AsDict().at("value");
				} catch (std::out_of_range) {
					continue;
				}

				std::vector<std::string> parameters;
				for(const auto& param : it_parameters.AsArray()) {
					parameters.push_back(param.AsString());
				}
				result.emplace(std::make_pair(it_user_param.AsString(), parameters));
			}
		}
	}
	return result;
}

std::map<std::pair<std::string, std::string>, std::vector<std::string>> json_reader::JsonReaderBase::ParseTwoParam() {
	std::map<std::pair<std::string, std::string>, std::vector<std::string>> result;

	if(document_.GetRoot().IsArray()) {
		for(const auto& cont : document_.GetRoot().AsArray()) {
			if(cont.IsDict() && cont.AsDict().size() == 2) {
				json::Node it_user_param_one;
				json::Node it_user_param_two;
				json::Node it_parameters;
				try {
					it_user_param_one = cont.AsDict().at("key");
					it_parameters = cont.AsDict().at("value");
				} catch (std::out_of_range) {
					continue;
				}

				std::vector<std::string> parameters;
				for(const auto& param : it_parameters.AsArray()) {
					parameters.push_back(param.AsString());
				}
				result.emplace(std::make_pair(
					std::make_pair(it_user_param_one.AsArray()[0].AsString()
						, it_user_param_one.AsArray()[1].AsString())
					, parameters));
			}
		}
	}
	return result;
}
