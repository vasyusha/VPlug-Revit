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
