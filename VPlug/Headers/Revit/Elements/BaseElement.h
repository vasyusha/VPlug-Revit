#pragma once

using namespace System;
using namespace System::Collections::Generic;

namespace Elements {

ref class BaseElement;

public ref class ParamResult {
public:
	property String^ Name;
	property String^ Value;
	property bool Filled;
};

public ref class BaseElement {
private:
	int id_;
	String^ uniqueId_;
	String^ name_;
	String^ categoryName_;
	int builtInCategory_;
	String^ builtInCategoryName_;
	List<ParamResult^>^ parameters_;

public:
	BaseElement();

	property int Id {
		int get();
		void set(int value);
	};

	property String^ UniqueId {
		String^ get();
		void set(String^ value);
	};

	property String^ Name {
		String^ get();
		void set(String^ value);
	};

	property String^ CategoryName {
		String^ get();
		void set(String^ value);
	};

	property int BuiltInCategory {
		int get();
		void set(int value);
	};

	property String^ BuiltInCategoryName {
		String^ get();
		void set(String^ value);
	};

	void AddParameter(String^ name, String^ value, bool filled);

	property IList<ParamResult^>^ Parameters {
		IList<ParamResult^>^ get();
	};
	
};

}