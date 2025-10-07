#pragma once

#include "Json.h"
using namespace System::Text;

namespace JsonReader {

public ref class CategorySpec {
public:
	String^ Id;
	String^ BuiltInCategory;
	String^ Name;
	List<String^>^ Parameters;
};

public ref class Filter {
public:
	String^ Name;
	String^ Value;
};

public ref class UserFilterSpec {
public:
	List<Filter^>^ Filters;
	List<String^>^ Parameters;
};

public ref class JsonReaderAuditParameter {
private:

public:
	static String^ GetStringOrThrow(Json::Dict d, String^ key);
	static List<String^>^ GetStringArrayOrThrow(Json::Dict d, String^ key);
	static CategorySpec^ ParseCategorySpec(Json::Node^ node);
	static List<CategorySpec^>^ LoadCategorySpecs(String^ path);
	static Filter^ GetFilterOrThrow(Json::Dict d, String^ key);
	static UserFilterSpec^ ParseUserFilterSpec(Json::Node^ node);
	static List<UserFilterSpec^>^ LoadUserFilterSpec(String^ path);
};

}// namespace JsonReader