#pragma once

using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;

namespace Json {

ref class Node;

using Dict = Dictionary<String^, Node^>^;
using Array = List<Node^>^;

public enum class Kind {
	Null,
	Array,
	Dict,
	Bool,
	Int,
	Double,
	String
};

public ref class Value {
private:
	Object^ boxed_;
	Kind kind_;
public:
	Value() : boxed_(nullptr), kind_(Kind::Null) {}
	Value(Array a)		: boxed_(a),	kind_(Kind::Array) {}
	Value(Dict d)		: boxed_(d),	kind_(Kind::Dict) {}
	Value(bool b)		: boxed_(b),	kind_(Kind::Bool) {}
	Value(int i)		: boxed_(i),	kind_(Kind::Int) {}
	Value(double d)		: boxed_(d),	kind_(Kind::Double) {}
	Value(String^ s)	: boxed_(s),	kind_(Kind::String) {}

	property Kind Type { Kind get() {return kind_;} }

	Array	AsArray();
	Dict	AsDict();
	bool	AsBool();
	int		AsInt();
	double	AsDouble();
	String^ AsString();

	static bool operator==(Value^ lhs, Value^ rhs);
	static bool operator!=(Value^ lhs, Value^ rhs);
	virtual bool Equals(Object^ obj) override;
	virtual int GetHashCode() override;
};

public ref class Node {
private:
	Value^ value_;
public:
	Node() : value_(gcnew Value()) {}
	Node(Array a)		: value_(gcnew Value(a)) {}
	Node(Dict d)		: value_(gcnew Value(d)) {}
	Node(bool b)		: value_(gcnew Value(b)) {}
	Node(int i)			: value_(gcnew Value(i)) {}
	Node(double d)		: value_(gcnew Value(d)) {}
	Node(String^ s)		: value_(gcnew Value(s)) {}
	Node(Value^ v)		: value_(v ? v : gcnew Value()) {}

	property Kind Type { Kind get() {return value_->Type;} }

	bool IsNull()		{ return Type == Kind::Null; }
	bool IsArray()		{ return Type == Kind::Array; }
	bool IsDict()		{ return Type == Kind::Dict; }
	bool IsBool()		{ return Type == Kind::Bool; }
	bool IsInd()		{ return Type == Kind::Int; }
	bool IsDouble()		{ return Type == Kind::Double; }
	bool IsString()		{ return Type == Kind::String; }

	Array   AsArray()	{ return value_->AsArray(); }
	Dict    AsDict()	{ return value_->AsDict(); }
	bool    AsBool()	{ return value_->AsBool(); }
	int     AsInt()		{ return value_->AsInt(); }
	double  AsDouble()	{ return value_->AsDouble(); }
	String^ AsString()	{ return value_->AsString(); }

	static bool operator==(Node^ a, Node^ b);
	static bool operator!=(Node^ a, Node^ b) { return !(a == b); }
	virtual bool Equals(Object^ obj) override;
	virtual int GetHashCode() override;
};

public ref class Document {
private:
	Node^ root_;
public:
	Document(Node^ root) : root_(root) {}
	property Node^ Root { Node^ get() { return root_; } }

	static bool operator==(Document^ a, Document^ b);
	static bool operator!=(Document^ a, Document^ b) { return !(a == b); }
	virtual bool Equals(Object^ obj) override;
	virtual int GetHashCode() override;
};

// Парсинг/печать
Document^ Load(TextReader^ input);     // читает JSON из TextReader
void      Print(Document^ doc, TextWriter^ output); // сериализует в JSON

}// namespace Json
