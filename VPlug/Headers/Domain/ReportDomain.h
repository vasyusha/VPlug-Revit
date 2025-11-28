#pragma once

#include "ParameterDomain.h"
#include "ElementDomain.h"

using namespace System;
using namespace System::Collections::Generic;

namespace MyDomain {

namespace Reports {

namespace Elements {

public ref class ElementReport {
private:
	MyDomain::Elements::Element^ element_;

public:
	property MyDomain::Elements::Element^ Element {
		MyDomain::Elements::Element^ get();
		void set(MyDomain::Elements::Element^ value);
	};
};

public ref class GroupReport {
private:
	MyDomain::Parameters::Audit::Group^ group_;
	IList<ElementReport^>^ elements_;
	IList<String^>^ checkedParameters_;

public:
	GroupReport();

	property MyDomain::Parameters::Audit::Group^ Group {
		MyDomain::Parameters::Audit::Group^ get();
		void set(MyDomain::Parameters::Audit::Group^ value);
	};
	property IList<ElementReport^>^ Elements {
		IList<ElementReport^>^ get();
		void set(IList<ElementReport^>^ value);
	};
	property IList<String^>^ CheckedParameters {
		IList<String^>^ get();
		void set(IList<String^>^ value);
	};

};

public ref class ResultReport {
private:
	String^ filePath_;
	String^ projectName_;
	String^ dateTimeStr_;
	IList<GroupReport^>^ groups_;
	MyDomain::Parameters::Audit::Result^ result_;

public:
	ResultReport();

	property String^ FilePath {
		String^ get();
		void set(String^ value);
	};
	property String^ ProjectName {
		String^ get();
		void set(String^ value);
	};
	property String^ DateTimeStr {
		String^ get();
		void set(String^ value);
	};
	property IList<GroupReport^>^ Groups {
		IList<GroupReport^>^ get();
		void set(IList<GroupReport^>^ value);
	};
	property MyDomain::Parameters::Audit::Result^ Result {
		MyDomain::Parameters::Audit::Result^ get();
		void set(MyDomain::Parameters::Audit::Result^ value);
	};
};

}//namespace Elements 

}//namespace Reports

}//namespace MyDomain
