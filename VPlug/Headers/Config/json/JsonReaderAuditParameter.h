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
	static String^ GetStringOrThrow(Json::Dict d, String^ key) {
		Json::Node^ n;
		if (!d->TryGetValue(key, n) || !n->IsString())
			throw gcnew InvalidOperationException("Key '" + key + "' is missing or not a string");

		return n->AsString();
	}

	static List<String^>^ GetStringArrayOrThrow(Json::Dict d, String^ key) {
		Json::Node^ n;
		if (!d->TryGetValue(key, n) || !n->IsArray())
			throw gcnew InvalidOperationException("Key '" + key + "' is missing or not an array");

		auto arr = n->AsArray();
		auto res = gcnew List<String^>();

		for each (Json::Node^ item in arr) {
			if (!item->IsString())
				throw gcnew InvalidOperationException("Array '" + key + "' must contain only strings");
			res->Add(item->AsString());
		}
		return res;
	}

	static CategorySpec^ ParseCategorySpec(Json::Node^ node) {
		if (!node->IsDict()) throw gcnew InvalidOperationException("Array element must be object");

		Json::Dict d = node->AsDict();

		auto spec = gcnew CategorySpec();
		spec->Id = GetStringOrThrow(d, "Id");                // в файле это строка
		spec->BuiltInCategory = GetStringOrThrow(d, "BuiltInCategory");
		spec->Name = GetStringOrThrow(d, "Name");
		spec->Parameters = GetStringArrayOrThrow(d, "Parameters");
		return spec;
	}

	static List<CategorySpec^>^ LoadCategorySpecs(String^ path) {
		auto sr = gcnew StreamReader(path, Encoding::UTF8);
		Json::Document^ doc = Json::Load(sr);
		Json::Node^ root = doc->Root;

		if(!root->IsArray()) throw gcnew InvalidOperationException("Root must be a JSON array");
		

		auto specs = gcnew List<CategorySpec^>();
		for each(Json::Node^ item in root->AsArray()) {
			specs->Add(ParseCategorySpec(item));
		}
		return specs;
	}

	static Filter^ GetFilterOrThrow(Json::Dict d, String^ key) {
		Json::Node^ n;
		if (!d->TryGetValue(key, n) || !n->IsArray())
			throw gcnew InvalidOperationException("Key '" + key + "' is missing or not an array");
		
		auto arr = n->AsArray();
		if(arr->Count != 2) 
			throw gcnew InvalidOperationException("Key '" + key + "': array size must be 2 (parameter name, value)");

		for each (Json::Node^ item in arr) {
			if (!item->IsString())
				throw gcnew InvalidOperationException("Array '" + key + "' must contain only strings");
		}

		Filter^ filter = gcnew Filter();
		filter->Name = arr[0]->AsString();
		filter->Value = arr[1]->AsString();

		return filter;
	}
	
	static UserFilterSpec^ ParseUserFilterSpec(Json::Node^ node) {
		if (!node->IsDict()) throw gcnew InvalidOperationException("Array element must be object");

		Json::Dict d = node->AsDict();
		auto spec = gcnew UserFilterSpec();
		spec->Filters = gcnew List<Filter^>();

		for(int i = 1; ; ++i) {
			String^ key = "Filter " + i.ToString();
			Json::Node^ n;
			if(!d->TryGetValue(key, n)) break;
			if(!n->IsArray())
				throw gcnew InvalidOperationException("Key '" + key + "' is not an array");
			auto arr = n->AsArray();
			if (arr->Count != 2 || !arr[0]->IsString() || !arr[1]->IsString())
				throw gcnew InvalidOperationException("Key '" + key + "' must be [string name, string value]");

			auto f = gcnew Filter();
			f->Name = arr[0]->AsString();
			f->Value = arr[1]->AsString();
			spec->Filters->Add(f);

		}

		spec->Parameters = GetStringArrayOrThrow(d, "Parameters");
		return spec;
	}

	static List<UserFilterSpec^>^ LoadUserFilterSpec(String^ path) {
	
		StreamReader^ sr = nullptr;

		try {
			sr = gcnew StreamReader(path, Encoding::UTF8);
			Json::Document^ doc = Json::Load(sr);
			Json::Node^ root = doc->Root;
			if(!root->IsArray()) throw gcnew InvalidOperationException("Root must be a JSON array");

			auto list = gcnew List<UserFilterSpec^>();
			for each(Json::Node^ item in root->AsArray()) {
				list->Add(ParseUserFilterSpec(item));
			}
			
			return list;			
		} finally {
			if(sr != nullptr) delete sr;
		}
	}
};

}// namespace JsonReader