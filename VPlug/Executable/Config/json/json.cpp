#pragma once
#include "..\..\..\Headlines\Config\json\json.h"

namespace json {

Node::Node(std::nullptr_t null) :value_(null) {}
Node::Node(Array array) : value_(std::move(array)) {}
Node::Node(Dict dict) : value_(std::move(dict)) {}
Node::Node(bool value) : value_(value) {}
Node::Node(int value) : value_(value) {}
Node::Node(double value) : value_(value) {}
Node::Node(std::string value) : value_(std::move(value)) {}
Node::Node(json::Node::Value value) : value_(std::move(value)) {}

bool Node::IsNull() const {
	return std::holds_alternative<std::nullptr_t>(value_);
}
bool Node::IsArray() const {
	return std::holds_alternative<Array>(value_);
}
bool Node::IsDict() const {
	return std::holds_alternative<Dict>(value_);
}
bool Node::IsBool() const {
	return std::holds_alternative<bool>(value_);
}
bool Node::IsInt() const {
	return std::holds_alternative<int>(value_);
}
bool Node::IsDouble() const {
	return std::holds_alternative<double>(value_) || Node::IsInt();
}
bool Node::IsPureDouble() const {
	return std::holds_alternative<double>(value_);
}
bool Node::IsString() const {
	return std::holds_alternative<std::string>(value_);
}

const Array& Node::AsArray() const {
	if(Node::IsArray()) {
		return std::get<Array>(value_);
	}
	throw std::logic_error("has no Array");
}

Array& Node::AsArray() {
	if (Node::IsArray()) {
		return std::get<Array>(value_);
	}
	throw std::logic_error("has no Array");
}

const Dict& Node::AsDict() const {
	if(Node::IsDict()) {
		return std::get<Dict>(value_);
	}
	throw std::logic_error("has no Dictionary");
}

Dict& Node::AsDict() {
	if (Node::IsDict()) {
		return std::get<Dict>(value_);
	}
	throw std::logic_error("has no Dictionary");
}

bool Node::AsBool() const {
	if(Node::IsBool()) {
		return std::get<bool>(value_);
	}
	throw std::logic_error("has no boolean");
}

int Node::AsInt() const {
	if(Node::IsInt()) {
		return std::get<int>(value_);
	}
	throw std::logic_error("has no Integer or Double");
}

double Node::AsDouble() const {
	if(Node::IsInt()) {
		return static_cast<double>(std::get<int>(value_));
	}
	if(Node::IsPureDouble()) {
		return std::get<double>(value_);
	}
	throw std::logic_error("has no Double Pure");
}

const std::string& Node::AsString() const {
	if(Node::IsString()) {
		return std::get<std::string>(value_);
	}
	throw std::logic_error("has no String");
}

bool Node::operator==(const Node& other) const {
	return value_ == other.value_;
}
bool Node::operator!=(const Node& other) const {
	return !(*this==other);
}

namespace {
	Node LoadNode(std::istream& input);

	Node LoadNull(std::istream& input) {
		std::string token;
		char ch;
		while(input >> ch && std::isalpha(ch)) {
			token += ch;
		}
		input.putback(ch);

		if(token == "null") return Node(nullptr);

		throw ParsingError("Invalid null value");
	}

	Node LoadArray(std::istream& input) {
		Array elements;
		char ch;

		while(input >> ch && std::isspace(ch));

		if(ch == ']') return Node(std::move(elements));
		input.putback(ch);

		while(true) {
			elements.push_back(LoadNode(input));

			while(input >> ch && std::isspace(ch));

			if(ch == ']') break;
			if(ch != ',') throw ParsingError("Error parse Array");
		}
		return Node(std::move(elements));
	}

	Node LoadString(std::istream& input);

	Node LoadDict(std::istream& input) {
		Dict dict;
		char ch;

		while(input >> ch && std::isspace(ch));
		if(ch == '}') return Node(std::move(dict));
		input.putback(ch);

		while(true) {
			Node key_node = LoadNode(input);
			if(!key_node.IsString()) throw ParsingError("Key no String");

			std::string key = key_node.AsString();

			while(input >> ch && std::isspace(ch));
			if(ch != ':') throw ParsingError("Dictionary no has ':'");

			dict[key] = LoadNode(input);

			while(input >> ch && std::isspace(ch));
			if(ch == '}') break;
			if(ch != ',') throw ParsingError("Dictionary no has ','");
		}
		return Node(std::move(dict));
	}

	Node LoadBool(std::istream& input) {
		std::string token;
		char ch;
		while(input >> ch && std::isspace(ch));
		input.putback(ch);

		if(token == "true") return Node(true);
		if(token == "false") return Node(false);

		throw ParsingError("Invalid value Boolean");
	}

	Node LoadNumber(std::istream& input) {
		std::string number;
		char ch;
		while(input.get(ch) && (std::isdigit(ch) || ch == '.'
			|| ch == 'e' || ch == 'E'
			|| ch == '-' || ch == '+'))
		{
			number += ch;
		}
		input.putback(ch);

		if(number.empty()) {
			throw ParsingError("Error parse Number");
		}
		if(number.find('.') != std::string::npos
			|| number.find('e') != std::string::npos
			|| number.find('E') != std::string::npos) {
			return std::stod(number);
		} else {
			return std::stoi(number);
		}
	}

	Node LoadString(std::istream& input) {
		std::string result;
		char ch;

		while(input.get(ch)) {
			if(ch == '//') {
				if(!input.get(ch)) {
					throw ParsingError("Error end of escape sequence");
				}
				switch(ch) {
					case 'r' : result += '\r'; break;
					case 'n' : result += '\n'; break;
					case 't' : result += '"'; break;
					case '\\' : result += '\\'; break;
					
					default: break;
				}
			} else if(ch == '"') {
				return Node(result);
			} else {
				result += ch;
			}
		}
		throw ParsingError("Error parse String");
	}
	//Tests
	using namespace Autodesk::Revit::UI;
	using namespace Autodesk::Revit::DB;
	using namespace Autodesk::Revit::Attributes;
	using namespace System;
	using namespace System::Drawing;
	using namespace System::Windows::Forms;
	using namespace System::Collections::Generic;
	Node LoadNode(std::istream& input) {
		char ch;
		while(input >> ch && std::isspace(ch));

		if(!input) throw ParsingError("Error create Node");

		if(ch == 'n') {
			input.putback(ch);
			return LoadNull(input);
		} else if(ch == '[') {
			return LoadArray(input);
		} else if(ch == '{') {
			return LoadDict(input);
		} else if(ch == 'f' || ch == 't') {
			input.putback(ch);
			return LoadBool(input);
		} else if(ch == '"') {
			return LoadString(input);
		} else if(std::isdigit(ch) || ch == '-' || ch == '+') {
			input.putback(ch);
			return LoadNode(input);
		}
		//Tests
		String^ str;
		str += ch;
		TaskDialog::Show("???", str);
		throw ParsingError("Error load Node");
	}

	void PrintValue(const std::string& value, std::ostream& output) {
		output << '"';
		for(char ch : value) {
			switch(ch) {
				case '\n' : output << "\\n"; break;
				case '\r' : output << "\\r"; break;
				case '\t' : output << "\\t"; break;
				case '\\' : output << "\\\\"; break;
				case '"' : output << "\\\""; break;
				default : output << ch; break;
			}
		}
		output << '"';
	}

	void PrintNode(const Node& node, std::ostream& output, int indent = 0) {
		const int indent_size = 4;
		std::string current_indent(indent, ' ');
		std::string next_indent(indent + indent_size, ' ');

		if(node.IsNull()) {
			output << "null";
		} else if(node.IsArray()) {
			const auto& arr = node.AsArray();
			if(arr.empty()) {
				output << "[]";
				return;
			}
			output << "[\n";
			for(size_t i = 0; i < arr.size(); ++i) {
				output << next_indent;
				PrintNode(arr[i], output, indent + indent_size);
				if(i + 1 < arr.size()) output << ",";
				output << "/n";
			}
			output << current_indent << "]";
		} else if(node.IsDict()) {
			const auto dict = node.AsDict();
			if(dict.empty()) {
				output << "{}";
				return;
			}
			output <<  "{\n";
			bool first = true;
			for(const auto& [key, value] : dict) {
				if(!first) output << ",\n";
				first = false;
				output << next_indent;
				PrintValue(key, output);
				output << ": ";
				PrintNode(value, output, indent + indent_size);
			}
			output << "\n" << current_indent << "}";
		} else if(node.IsBool()) {
			output << (node.AsBool() ? "true" : "false");
		} else if(node.IsInt()) {
			output << node.AsInt();
		} else if(node.IsPureDouble()) {
			output << node.AsDouble();
		} else if(node.IsString()) {
			output << node.AsString();
		}
	}
}//namespace

Document::Document(Node root) : root_(std::move(root)) {}

const Node& Document::GetRoot() const {
	return root_;
}

Document Load(std::istream& input) {
	return Document{LoadNode(input)};
}

void Print(const Document& doc, std::ostream& output) {
	PrintNode(doc.GetRoot(), output, 0);
}

bool Document::operator==(const Document& other) const {
	return root_ == other.GetRoot();
}

bool Document::operator!=(const Document& other) const {
	//return !(*this == other);?
	return root_ != other.GetRoot();
}

bool operator==(const Document& lhs, const Document& rhs) {
	return lhs.GetRoot() == rhs.GetRoot();
}

bool operator!=(const Document& lhs, const Document& rhs) {
	return !(lhs.GetRoot() == rhs.GetRoot());
}

} //namespace json