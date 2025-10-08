#include "..\..\..\Headers\Config\json\Json.h"

using namespace System::Globalization;
using namespace System::Text;

namespace Json {

Array Value::AsArray() {
	if(kind_ != Kind::Array) throw gcnew InvalidOperationException("Value is not Array");
	return safe_cast<Array>(boxed_);
}
Dict Value::AsDict() {
	if(kind_ != Kind::Dict) throw gcnew InvalidOperationException("Value is not Dict");
	return safe_cast<Dict>(boxed_);
}
bool Value::AsBool() {
	if(kind_ != Kind::Bool) throw gcnew InvalidOperationException("Value is not Bool");
	return safe_cast<bool>(boxed_);
}
int Value::AsInt() {
	if(kind_ != Kind::Int) throw gcnew InvalidOperationException("Value is not Int");
	return safe_cast<int>(boxed_);
}
double Value::AsDouble() {
	if(kind_ != Kind::Double) throw gcnew InvalidOperationException("Value is not Double");
	return safe_cast<double>(boxed_);
}
String^ Value::AsString() {
	if(kind_ != Kind::String) throw gcnew InvalidOperationException("Value is not String");
	return safe_cast<String^>(boxed_);
}

static bool SeqEqual(Array a, Array b) {
	if(Object::ReferenceEquals(a, b)) return true;
	if(a == nullptr || b == nullptr) return false;
	if(a->Count != b->Count) return false;
	for(int i = 0; i < a->Count; ++i) {
		if(!a[i]->Equals(b[i])) return false;
	}
	return true;
}

static bool DictEqual(Dict a, Dict b) {
	if(Object::ReferenceEquals(a, b)) return true;
	if(a == nullptr || b == nullptr) return false;
	if(a->Count != b->Count) return false;
	for each(KeyValuePair<String^, Node^> kvp in a) {
		Node^ other;
		if(!b->TryGetValue(kvp.Key, other)) return false;
		if(!kvp.Value->Equals(other)) return false;
	}
	return true;
}
//???
static int CombineHash(int h1, int h2) {
	long long x = (static_cast<long long>(h1) << 1) ^ h2;
	x ^= (x >> 33);
	return static_cast<int>(x);
}

bool Value::Equals(Object^ obj) {
	Value^ other = dynamic_cast<Value^>(obj);
	if(other == nullptr) return false;
	if(this->kind_ != other->kind_) return false;

	switch (this->kind_) {
		case Kind::Null : return true;
		case Kind::Bool : return this->AsBool() == other->AsBool();
		case Kind::Int : return this->AsInt() == other->AsInt();
		case Kind::Double : return this->AsDouble() == other->AsDouble();
		case Kind::String : return String::Equals(this->AsString(), other->AsString(), StringComparison::Ordinal);
		case Kind::Array : return SeqEqual(this->AsArray(), other->AsArray());
		case Kind::Dict : return DictEqual(this->AsDict(), other->AsDict());
		default: return false;
	}
}

int Value::GetHashCode() {
	int h = static_cast<int>(kind_) * 397;
	switch (kind_) {
		case Kind::Null : 
			break;
		case Kind::Bool : h = CombineHash(h, AsBool().GetHashCode()); 
			break;
		case Kind::Int : h = CombineHash(h, AsInt().GetHashCode());
			break;
		case Kind::Double : h = CombineHash(h, AsDouble().GetHashCode());
			break;
		case Kind::String : h = CombineHash(h, AsString()->GetHashCode());
			break;
		case Kind::Array : 
			for each(Node^ n in AsArray()) {
				h = CombineHash(h, n->GetHashCode());
			}
			break;
		case Kind::Dict : 
			for each(KeyValuePair<String^, Node^> kvp in AsDict()) {
				h = CombineHash(h, CombineHash(kvp.Key->GetHashCode(), kvp.Value->GetHashCode()));
			}
			break;
	}
	return h;
}

bool Value::operator==(Value^ lhs, Value^ rhs) {
	if(Object::ReferenceEquals(lhs, rhs)) return true;
	if(lhs == nullptr || rhs == nullptr) return false;
	return lhs->Equals(rhs);
}

bool Value::operator!=(Value^ lhs, Value^ rhs) {
	return !(lhs == rhs);
}

bool Node::Equals(Object^ obj) {
	Node^ other = dynamic_cast<Node^>(obj);
	if(other == nullptr) return false;
	if(this->value_ == nullptr) return other->value_ == nullptr;
	return this->value_->Equals(other->value_);
}

int Node::GetHashCode() {
	return value_ ? value_->GetHashCode() : 0;
}

bool Node::operator==(Node^ lhs, Node^ rhs) {
	if(Object::ReferenceEquals(lhs, rhs)) return true;
	if(lhs == nullptr || rhs == nullptr) return false;
	return lhs->Equals(rhs);
}

bool Document::Equals(Object^ obj) {
	Document^ other = dynamic_cast<Document^>(obj);
	if(other == nullptr) return false;
	return this->Root->Equals(other->Root);
}

int Document::GetHashCode() {
	return Root ? Root->GetHashCode() : 0;
}

bool Document::operator==(Document^ lhs, Document^ rhs) {
	if(Object::ReferenceEquals(lhs, rhs)) return true;
	if(lhs == nullptr || rhs == nullptr) return false;
	return lhs->Equals(rhs);
}

namespace {
ref class CharReader {
private:
	TextReader^ r_;
	int cur_; // текущий code unit или -2 (не читали) / -1 (EOF)
	int pos_; // счётчик позиций (для диагностики)
public:
	CharReader(TextReader^ r) : r_(r), cur_(-2), pos_(0) {}
	int Peek() {
		if(cur_ == -2) { 
			cur_ = r_->Read(); 
		}
		return cur_;
	}
	int Read() {
		int c = Peek();
		cur_ = r_->Read();
		++pos_;
		return c;
	}
	void Expect(int ch) {
		int c = Read();
		if(c != ch) {
			throw gcnew InvalidOperationException(String::Format("Expected '{0}', got '{1}' at pos {2}",
				(wchar_t)ch, (c < 0 ? L'∅' : (wchar_t)c), pos_));
		}
	}
	int Position() {
		return pos_;
	}
};

inline bool IsWS(int c) {
	return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

void SkipWS(CharReader^ rd) {
	int c = rd->Peek();
	while(c != -1 && IsWS(c)) {
		rd->Read();
		c = rd->Peek();
	}
}

int Read4Hex(CharReader^ rd) {
	int v = 0;
	for (int i = 0; i < 4; ++i) {
		int h = rd->Read();
		if (h == -1) throw gcnew InvalidOperationException("Unterminated \\uXXXX escape");
		int d;
		if (h >= '0' && h <= '9') d = h - '0';
		else if (h >= 'A' && h <= 'F') d = 10 + (h - 'A');
		else if (h >= 'a' && h <= 'f') d = 10 + (h - 'a');
		else throw gcnew InvalidOperationException("Invalid hex digit in \\uXXXX");
		v = (v << 4) | d;
	}
	return v;
}

String^ ParseString(CharReader^ rd) {
	rd->Expect('"');
	StringBuilder^ sb = gcnew StringBuilder();
	while(true) {
		int c = rd->Read();
		if(c == -1) throw gcnew InvalidOperationException("Unterminated string");
		if(c == '"') break;
		if(c == '\\') {
			int e = rd->Read();
			if (e == -1) throw gcnew InvalidOperationException("Unterminated escape");
			switch (e) {
				case '"' : sb->Append('"');
					break;
				case '\\' : sb->Append('\\');
					break;
				case '/' : sb->Append('/');
					break;
				case 'b' : sb->Append('\b');
					break;
				case 'f' : sb->Append('\f');
					break;
				case 'n' : sb->Append('\n');
					break;
				case 'r' : sb->Append('\r');
					break;
				case 't' : sb->Append('\t');
					break;
				case 'u' : {
					int u1 = Read4Hex(rd);
					if(u1 >= 0xD800 && u1 <= 0xDBFF) {
						int bs = rd->Read();
						int u = rd->Read();
						if (bs != '\\' || u != 'u')
							throw gcnew InvalidOperationException("Expected second surrogate \\uDDDD");
						int u2 = Read4Hex(rd);
						if (!(u2 >= 0xDC00 && u2 <= 0xDFFF))
							throw gcnew InvalidOperationException("Invalid low surrogate");
						int codepoint = 0x10000 + ((u1 - 0xD800) << 10) + (u2 - 0xDC00);
						sb->Append(Char::ConvertFromUtf32(codepoint));
					} else {
						sb->Append((wchar_t)u1);
					}
					break;
				}
				default :
					throw gcnew InvalidOperationException("Unknown escape: \\" + ((wchar_t)e).ToString());
			} 
		} else {
			sb->Append((wchar_t)c);
		}
	}
	return sb->ToString();
}

Node^ ParseValue(CharReader^ rd);

Node^ ParseArray(CharReader^ rd) {
	rd->Expect('[');
	SkipWS(rd);
	Array a = gcnew List<Node^>();
	if(rd->Peek() == ']') {
		rd->Read();
		return gcnew Node(a);
	}
	while(true) {
		SkipWS(rd);
		a->Add(ParseValue(rd));
		SkipWS(rd);
		int c = rd->Read();
		if(c == ']') break;
		if(c != ',') throw gcnew InvalidOperationException("Expected ',' or ']'");
	}
	return gcnew Node(a);
}

Node^ ParseObject(CharReader^ rd) {
	rd->Expect('{');
	SkipWS(rd);
	Dict d = gcnew Dictionary<String^, Node^>();
	if(rd->Peek() == '}') {
		rd->Read();
		return gcnew Node(d);
	}
	while(true) {
		SkipWS(rd);
		if(rd->Peek() != '"') throw gcnew InvalidOperationException("Object key must be a string");
		String^ key = ParseString(rd);
		SkipWS(rd);
		rd->Expect(':');
		SkipWS(rd);
		Node^ val = ParseValue(rd);
		d[key] = val;
		SkipWS(rd);
		int c = rd->Read();
		if(c == '}') break;
		if (c != ',') throw gcnew InvalidOperationException("Expected ',' or '}'");
	}
	return gcnew Node(d);
}

Node^ ParseLiteral(CharReader^ rd) {
	int c = rd->Peek();
	if(c == 't') {
		rd->Expect('t');
		rd->Expect('r');
		rd->Expect('u');
		rd->Expect('e');
		return gcnew Node(true);
	}
	if(c == 'f') {
		rd->Expect('f');
		rd->Expect('a');
		rd->Expect('l');
		rd->Expect('s');
		rd->Expect('e');
		return gcnew Node(false);
	}
	if(c == 'n') {
		rd->Expect('n');
		rd->Expect('u');
		rd->Expect('l');
		rd->Expect('l');
		return gcnew Node(gcnew Value());
	}
	throw gcnew InvalidOperationException("Unknown literal");
}

Node^ ParseNumber(CharReader^ rd) {
	StringBuilder^ sb = gcnew StringBuilder();
	int c = rd->Peek();

	if(c == '-') {
		sb->Append(wchar_t('-'));
		rd->Read();
		c = rd->Peek();
	}
	if(c == '0') {
		sb->Append('0');
		rd->Read();
		c = rd->Peek();
		if (c >= '0' && c <= '9') throw gcnew InvalidOperationException("Leading zeros are not allowed");
	} else {
		if(c < '1' || c > '9') throw gcnew InvalidOperationException("Digit expected");
		while(c >= '0' && c <= '9') {
			sb->Append(wchar_t(c));
			rd->Read();
			c = rd->Peek();
		}
	}

	bool IsDouble = false;
	if(c == '.') {
		IsDouble = true;
		//!?
		sb->Append('.');
		rd->Read();
		c = rd->Peek();
		if (c < '0' || c > '9') throw gcnew InvalidOperationException("Digit required after decimal point");
		while (c >= '0' && c <= '9') {
			sb->Append((wchar_t)c);
			rd->Read(); 
			c = rd->Peek();
		}
	}
	if(c == 'e' || c == 'E') {
		IsDouble = true;
		sb->Append((wchar_t)c);
		rd->Read();
		c = rd->Peek();
		if(c == '+' || c == '-') {
			sb->Append((wchar_t)c);
			rd->Read();
			c = rd->Peek();
		}
		if (c < '0' || c > '9') throw gcnew InvalidOperationException("Digit required in exponent");
		while (c >= '0' && c <= '9') {
			sb->Append((wchar_t)c);
			rd->Read();
			c = rd->Peek();
		}
	}
	
	String^ s = sb->ToString();
	auto inv = CultureInfo::InvariantCulture;

	if(IsDouble) {
		double d = Double::Parse(s, NumberStyles::Float, inv);
		return gcnew Node(d);
	} else {
		long long v = Int64::Parse(s, NumberStyles::Integer, inv);
		if(v < Int32::MinValue || v > Int32::MaxValue) {
			throw gcnew InvalidOperationException("Integer out of Int32 range");
		}
		return gcnew Node((int)v);
	}
}

Node^ ParseValue(CharReader^ rd) {
	SkipWS(rd);
	int c =	rd->Peek();
	if(c == -1) {
		throw gcnew InvalidOperationException("Unexpected EOF");
	}

	switch (c) {
		case '"' : return gcnew Node(ParseString(rd));
		case '{' : return ParseObject(rd);
		case '[' : return ParseArray(rd);
		case 't' : case 'f' : case 'n' : return ParseLiteral(rd);
		default : {
			if(c == '-' || (c >= '0' && c <= '9')) return ParseNumber(rd);
			throw gcnew InvalidOperationException("Unexpected char: " + ((wchar_t)c).ToString());
		}
	}
}

} //namespace

Document^ Load(TextReader^ input) {
	if(input == nullptr) throw gcnew ArgumentNullException("input");
	CharReader^ rd = gcnew CharReader(input);
	Node^ root = ParseValue(rd);
	SkipWS(rd);
	if (rd->Peek() != -1) {
		throw gcnew InvalidOperationException("Extra data after root JSON value");
	}
	return gcnew Document(root);
}

//===========================================================
// 6) Печать (сериализация) в JSON с экранированием
//===========================================================

static void WriteEscapedString(String^ s, TextWriter^ w) {
	w->Write('"');
	for each (wchar_t ch in s) {
		switch (ch) {
			case '"':  w->Write("\\\""); break;
			case '\\': w->Write("\\\\"); break;
			case '\b': w->Write("\\b");  break;
			case '\f': w->Write("\\f");  break;
			case '\n': w->Write("\\n");  break;
			case '\r': w->Write("\\r");  break;
			case '\t': w->Write("\\t");  break;
			default:
			if (ch < 0x20) {
				w->Write(String::Format("\\u{0:X4}", (int)ch));
			} else {
				w->Write(ch);
			}
		}
	}
	w->Write('"');
}

static void WriteNode(Node^ n, TextWriter^ w, int indent, bool pretty);

static void WriteArray(Array a, TextWriter^ w, int indent, bool pretty) {
	if (a == nullptr || a->Count == 0) { w->Write("[]"); return; }
	if (!pretty) {
		w->Write('[');
		for (int i = 0; i < a->Count; ++i) {
			if (i) w->Write(',');
			WriteNode(a[i], w, 0, false);
		}
		w->Write(']');
		return;
	}
	String^ pad = gcnew String(' ', indent);
	String^ pad2 = gcnew String(' ', indent + 2);
	w->Write("[\n");
	for (int i = 0; i < a->Count; ++i) {
		w->Write(pad2);
		WriteNode(a[i], w, indent + 2, true);
		if (i + 1 < a->Count) w->Write(',');
		w->Write('\n');
	}
	w->Write(pad);
	w->Write(']');
}

static void WriteDict(Dict d, TextWriter^ w, int indent, bool pretty) {
	if (d == nullptr || d->Count == 0) { w->Write("{}"); return; }
	if (!pretty) {
		w->Write('{');
		bool first = true;
		for each (KeyValuePair<String^, Node^> kv in d) {
			if (!first) w->Write(',');
			first = false;
			WriteEscapedString(kv.Key, w);
			w->Write(':');
			WriteNode(kv.Value, w, 0, false);
		}
		w->Write('}');
		return;
	}
	String^ pad = gcnew String(' ', indent);
	String^ pad2 = gcnew String(' ', indent + 2);
	w->Write("{\n");
	bool first = true;
	for each (KeyValuePair<String^, Node^> kv in d) {
		if (!first) w->Write(",\n");
		first = false;
		w->Write(pad2);
		WriteEscapedString(kv.Key, w);
		w->Write(": ");
		WriteNode(kv.Value, w, indent + 2, true);
	}
	w->Write('\n');
	w->Write(pad);
	w->Write('}');
}

static void WriteNode(Node^ n, TextWriter^ w, int indent, bool pretty) {
	auto inv = CultureInfo::InvariantCulture;

	switch (n->Type) {
		case Kind::Null:   w->Write("null"); break;
		case Kind::Bool:   w->Write(n->AsBool() ? "true" : "false"); break;
		case Kind::Int:    w->Write(n->AsInt().ToString(inv)); break;
		case Kind::Double: w->Write(n->AsDouble().ToString("R", inv)); break; // "R" -> round-trip
		case Kind::String: WriteEscapedString(n->AsString(), w); break;
		case Kind::Array:  WriteArray(n->AsArray(), w, indent, pretty); break;
		case Kind::Dict:   WriteDict(n->AsDict(), w, indent, pretty); break;
	}
}

void Print(Document^ doc, TextWriter^ output) {
	if (doc == nullptr) throw gcnew ArgumentNullException("doc");
	if (output == nullptr) throw gcnew ArgumentNullException("output");
	// Красивый вывод с отступами. Если нужен компактный — поменяй флаг на false.
	WriteNode(doc->Root, output, 0, true);
}


} //namespace Json













