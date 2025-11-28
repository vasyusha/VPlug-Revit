#pragma once

#include "ParameterDomain.h"

using namespace System;
using namespace System::Collections::Generic;

namespace MyDomain {

namespace Elements {

public ref class Element {
private:
	int id_;
	String^ uniqueId_;
	String^ name_;
	String^ categoryName_;
	int builtInCategory_;
	String^ builtInCategoryName_;
	IList<Parameters::Parameter^>^ parameters_;

public:
	Element();

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
	property IList<Parameters::Parameter^>^ Param {
		IList<Parameters::Parameter^>^ get();
		void set(IList<Parameters::Parameter^>^ value);
	};
};

}//namespace Elements

}//namespace MyDomain

