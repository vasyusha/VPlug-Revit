#pragma once

#include "ParameterDomain.h"

using namespace System;
using namespace System::Collections::Generic;

namespace MyDomain {

namespace Elements {

public ref class Element {
protected:
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
	property IList<MyDomain::Parameters::Parameter^>^ Parameters {
		IList<MyDomain::Parameters::Parameter^>^ get();
		void set(IList<MyDomain::Parameters::Parameter^>^ value);
	};
};

public ref class WallElement : public Element {
private:
	double area_;
	bool hasOpening_;
	int countOpenings_;
	/*Логические дочерние элементы проёмов, включая FindInserts(addRectOpenings, includeShadows)*/
	IList<Element^>^ logicChildrenOpenings_;
	
public:
	property double Area {
		double get();
		void set(double value);
	};
	property bool HasOpening {
		bool get();
		void set(bool value);
	};
	property int CountOpenings {
		int get();
		void set(int value);
	};
	property IList<Element^>^ LogicChildrenOpenings {
		IList<Element^>^ get();
		void set(IList<Element^>^ value);
	};
};

namespace AuditParameters {

public ref class AuditElement {
private:
	Element^ element_;
	bool pass_;
	int totalParams_;
	int passParams_;
	int failParams_;
	int filledParams_;
	int emptyParams_;
	int missingParams_;
	int percent_;

public:
	property Element^ Element {
		MyDomain::Elements::Element^ get();
		void set(MyDomain::Elements::Element^ value);
	};
	property bool Pass{
		bool get();
		void set(bool value);
	};
	property int TotalParams {
		int get();
		void set(int value);
	};
	property int PassParams {
		int get();
		void set(int value);
	};
	property int FailParams {
		int get();
		void set(int value);
	};
	property int FilledParams {
		int get();
		void set(int value);
	};
	property int EmptyParams {
		int get();
		void set(int value);
	};
	property int MissingParams {
		int get();
		void set(int value);
	};
	property int Percent {
		int get();
		void set(int value);
	};
};

public ref class AuditGroup {
private:
	String^ name_;
	bool pass_;
	int totalElements_;
	int passElements_;
	int failElements_;
	int totalParams_;
	int passParams_;
	int failParams_;
	int emptyParams_;
	int missingParams_;
	int percent_;
	IList<AuditElement^>^ elements_;
	IList<String^>^ checkedParameters_;

public:
	AuditGroup();

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
	property int FailParams {
		int get();
		void set(int value);
	};
	property int EmptyParams {
		int get();
		void set(int value);
	};
	property int MissingParams {
		int get();
		void set(int value);
	};
	property int Percent {
		int get();
		void set(int value);
	};
	property IList<AuditElement^>^ Elements {
		IList<AuditElement^>^ get();
		void set(IList<AuditElement^>^ value);
	};
	property IList<String^>^ CheckedParameters {
		IList<String^>^ get();
		void set(IList<String^>^ value);
	};
};

public ref class AuditResult {
private:
	bool pass_;
	int totalGroups_;
	int passGroups_;
	int failGrpups_;
	//Req = requirements
	int reqElementPass_; //Требования к элементу ок
	int reqElementTotal_; //Требования к элементу всего
	int reqParamPass_; //Требования к параметру ок
	int reqParamTotal_; //Требования к параметру всего
	int percent_;
	IList<AuditGroup^>^ groups_;	

public:
	AuditResult();	

	property bool Pass {
		bool get();
		void set(bool value);
	};
	property int TotalGroups {
		int get();
		void set(int value);
	};
	property int PassGroups {
		int get();
		void set(int value);
	};
	property int FailGroup {
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
	property IList<AuditGroup^>^ Groups {
		IList<AuditGroup^>^ get();
		void set(IList<AuditGroup^>^ value);
	};
};

}//namespace AuditParameters

namespace AuditWallOpenings {

public ref struct Scop {
	String^ name;
	String^ value;
	
	/*
	bool operator==(Scop^ other) {
		return name == other->name && value == other->value;
	}
	bool operator!=(Scop^ other) {
		return !(this == other);
	}
	*/
};
public ref class AuditOpening {
private:
	Element^ element_;

public:
	property Element^ Element {
		MyDomain::Elements::Element^ get();
		void set(MyDomain::Elements::Element^ value);
	};
};

public ref class AuditWallElement {
private:
	List<Scop^>^ scops_;
	WallElement^ wallElement_;
	List<AuditOpening^>^ auditOpenings_;

public:
	property List<Scop^>^ Scops {
		List<Scop^>^ get();
		void set(List<Scop^>^ value);
	};
	property WallElement^ WallElement {
		MyDomain::Elements::WallElement^ get();
		void set(MyDomain::Elements::WallElement^ value);
	};
	property List<AuditOpening^>^ AuditOpenings {
		List<AuditOpening^>^ get();
		void set(List<AuditOpening^>^ value);
	};

};

public ref class AuditWallGroup {
private:
	//Имя фильтра-значения.
	String^ name_;
	List<Scop^>^ scops_;
	int totalWalls_;
	double totalArea_;
	int totalOpenings_;
	double totalAreaWallsWithOpenings_;
	double totalAreaWallsWithoutOpenings_;
	IList<AuditWallElement^>^ auditWallElements_;
	List<AuditOpening^>^ auditOpenings_;

public:
	AuditWallGroup();

	property String^ Name {
		String^ get();
		void set(String^ value);
	};
	property List<Scop^>^ Scops {
		List<Scop^>^ get();
		void set(List<Scop^>^ valud);
	};
	property int TotalWalls {
		int get();
		void set(int value);
	};
	property double TotalArea {
		double get();
		void set(double value);
	};
	property int TotalOpenings {
		int get();
		void set(int value);
	};
	property double TotalAreaWallsWithOpenings {
		double get();
		void set(double value);
	};
	property double TotalAreaWallsWithoutOpenings {
		double get();
		void set(double value);
	};
	property IList<AuditWallElement^>^ AuditWallElements {
		IList<AuditWallElement^>^ get();
		void set(IList<AuditWallElement^>^ value);
	};
	property List<AuditOpening^>^ AuditOpenings {
		List<AuditOpening^>^ get();
		void set(List<AuditOpening^>^ value);
	};
};

public ref class AuditResult {
private:
	IList<AuditWallElement^>^ auditWallElements_;
	IList<AuditWallGroup^>^ auditWallGroups_;

public:
	AuditResult();

	property IList<AuditWallElement^>^ AuditWallElements {
		IList<AuditWallElement^>^ get();
		void set(IList<AuditWallElement^>^ value);
	};
	property IList<AuditWallGroup^>^ AuditWallGroups {
		IList<AuditWallGroup^>^ get();
		void set(IList<AuditWallGroup^>^ value);
	};
};

}//namespace AuditWallOpenings

}//namespace Elements

}//namespace MyDomain

