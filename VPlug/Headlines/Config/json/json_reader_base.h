#pragma once
#include "json.h"

#include <fstream>
#include <string>

namespace json_reader {

class JsonReaderBase {
private:
	json::Document document_;

public:
	JsonReaderBase(std::istream& input);

	std::map<std::string, std::string> ParseMapStringString();
	std::map<std::string, std::vector<std::string>> ParseMapStringVectorString();
	std::map<std::string, std::map<std::string, std::string>> ParseMapStringMapStringString();
	std::map<std::pair<std::string, std::string>, std::vector<std::string>> ParseMapPairStringStringVectorString();

	std::vector<std::map<std::string, std::string>> ParseVectorMapStringString();
};

}