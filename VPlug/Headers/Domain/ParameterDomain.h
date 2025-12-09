#pragma once

using namespace System;
using namespace System::Collections::Generic;

namespace MyDomain {

namespace Parameters {

public enum class ParameterStatus {
	Filled,
	Empty,
	Missing
};

public ref class Parameter {
private:
	String^ name_;
	String^ value_;
	bool filled_;
	ParameterStatus status_;

public:
	property String^ Name {
		String^ get();
		void set(String^ value);
	};
	property String^ Value {
		String^ get();
		void set(String^ value);
	};
	property bool Filled {
		bool get();
		void set(bool value);
	};
	property ParameterStatus Status {
		ParameterStatus get();
		void set(ParameterStatus value);
	};
};

}//namespace Parameters

}//namespace MyDomain