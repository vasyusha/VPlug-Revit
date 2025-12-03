#pragma once

#include "ElementDomain.h"

using namespace System;
using namespace System::Collections::Generic;

namespace MyDomain {

namespace AuditParameterReport {

public ref class ResultReport {
private:
	String^ filePath_;
	String^ projectName_;
	String^ dateTimeStr_;
	MyDomain::Elements::AuditParameters::AuditResult^ result_;

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

	property MyDomain::Elements::AuditParameters::AuditResult^ Result {
		MyDomain::Elements::AuditParameters::AuditResult^ get();
		void set(MyDomain::Elements::AuditParameters::AuditResult^ value);
	};
};

}//namespace AuditPrameterReport

}//namespace MyDomain
