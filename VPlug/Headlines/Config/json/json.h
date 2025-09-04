#pragma once
#include <algorithm>
#include <cctype>
#include <iostream>
#include <initializer_list>
#include <istream>
#include <map>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

namespace json {

class Node;

using Dict = std::map<std::string, Node>;
using Array = std::vector<Node>;

class ParsingError : public std::runtime_error {
public:
	using runtime_error::runtime_error;
};

class Node {
public:
	using Value = std::variant<std::nullptr_t, Array, Dict, bool, int, double, std::string>;
	
	Node() = default;
	Node(std::nullptr_t null);
	Node(Array array);
	Node(Dict dict);
	Node(bool value);
	Node(int value);
	Node(double value);
	Node(std::string value);
	Node(Value v);

	bool IsNull() const;
	bool IsArray() const;
	bool IsDict() const;
	bool IsBool() const;
	bool IsInt() const;
	bool IsDouble() const;
	bool IsPureDouble() const;
	bool IsString() const;

	const Array& AsArray() const;
	const Dict& AsDict() const;
	Array& AsArray();
	Dict& AsDict();
	bool AsBool() const;
	int AsInt() const;
	double AsDouble() const;
	const std::string& AsString() const;

	bool operator==(const Node& other) const;
	bool operator!=(const Node& other) const;

	const Value& GetValue() const {return value_;}
private:
	Value value_;
};

class Document {
public:
	explicit Document(Node root);
	const Node& GetRoot() const;
	bool operator==(const Document& other) const;
	bool operator!=(const Document& other) const;

private:
	Node root_;
};

Document Load(std::istream& input);

void Print(const Document& doc, std::ostream& output);

}