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

namespace Audit {

public ref class Group {
private:
	String^ name_;
	bool pass_;
	int totalElements_;
	int passElements_;
	int failElements_;
	int totalParams_;
	int passParams_;
	int missingParams_;
	int noParams_;
	int percent_;

public:
	property String^ Name {
		String^ get();
		void set(String^ value);
	};
	property bool Pass {
		bool get();
		void set(bool value);
	};
	property int TotalElements {
		int get();
		void set(int value);
	};
	property int PassElements {
		int get();
		void set(int value);
	};
	property int FailElements {
		int get();
		void set(int value);
	};
	property int TotalParams {
		int get();
		void set(int value);
	};
	property int PassParams {
		int get();
		void set(int value);
	};
	property int MissingParams {
		int get();
		void set(int value);
	};
	property int NoParams {
		int get();
		void set(int value);
	};
	property int Percent {
		int get();
		void set(int value);
	};
};

public ref class Result {
private:
	bool pass_;
	int groupPass_;
	int groupTotal_;
	//Req = requirements
	int reqElementPass_; //Требования к элементу ок
	int reqElementTotal_; //Требования к элементу всего
	int reqParamPass_; //Требования к параметру ок
	int reqParamTotal_; //Требования к параметру всего
	int percent_;
	IList<Group^>^ groups_;	

public:
	Result();	

	property bool Pass {
		bool get();
		void set(bool value);
	};
	property int GroupPass {
		int get();
		void set(int value);
	};
	property int GroupTotal {
		int get();
		void set(int value);
	};
	property int ReqElementPass{
		int get();
		void set(int value);
	};
	property int ReqElementTotal {
		int get();
		void set(int value);
	};
	property int ReqParamPass {
		int get();
		void set(int value);
	};
	property int ReqParamTotal {
		int get();
		void set(int value);
	};
	property int Percent {
		int get();
		void set(int value);
	};
	property IList<Group^>^ Groups {
		IList<Group^>^ get();
		void set(IList<Group^>^ value);
	};
};

}//namespace Audit

}//namespace Parameters

}//namespace MyDomain