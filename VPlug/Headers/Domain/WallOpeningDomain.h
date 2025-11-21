#pragma once

using namespace System;
using namespace System::Collections::Generic;

namespace MyDomain {

namespace WallOpening {

public ref class OpeningInfo {
private:
	int id_;
	String^ name_;
	String^ categoryName_;

public:
	property int Id {
		int get();
		void set(int value);
	};

	property String^ Name {
		String^ get();
		void set(String^ value);
	};

	property String^ CategoryName {
		String^ get();
		void set(String^ value);
	};
};

public ref class WallElementInfo {
private:
	int id_;
	String^ name_;
	String^ categoryName_;
	double area_;
	int countOpenings_;
	IList<OpeningInfo^>^ openings_;

public:
	WallElementInfo();

	property int Id {
		int get();
		void set(int value);
	};

	property String^ Name {
		String^ get();
		void set(String^ value);
	};

	property String^ CategoryName {
		String^ get();
		void set(String^ value);
	};

	property double Area {
		double get();
		void set(double value);
	};

	property int CountOpenings {
		int get();
		void set(int value);
	};

	property IList<OpeningInfo^>^ Openings {
		IList<OpeningInfo^>^ get();
		void set(IList<OpeningInfo^>^ value);
	};
};

public ref class WallTypeInfo {
private:
	String^ name_;
	int totalWalls_;
	double totalArea_;
	int totalOpenings_;
	double totalAreaWallsWithOpenings_;
	double totalAreaWallsWithoutOpenings_;
	IList<OpeningInfo^>^ openings_;

public:
	WallTypeInfo();

	property String^ Name {
		String^ get();
		void set(String^ value);
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

	property IList<OpeningInfo^>^ Openings {
		IList<OpeningInfo^>^ get();
		void set(IList<OpeningInfo^>^ value);
	};
};

public ref class WallOpeningReport {
private:
	String^ projectName_;
	String^ dateTimeStr_;
	IList<WallElementInfo^>^ wallElements_;
	IDictionary<String^, WallTypeInfo^>^ wallTypes_;

public:
	WallOpeningReport();

	property String^ ProjectName {
		String^ get();
		void set(String^ value);
	};

	property String^ DateTimeStr {
		String^ get();
		void set(String^ value);
	};

	property IList<WallElementInfo^>^ WallElemnts {
		IList<WallElementInfo^>^ get();
		void set(IList<WallElementInfo^>^ value);
	};

	property IDictionary<String^, WallTypeInfo^>^ WallTypes {
		IDictionary<String^, WallTypeInfo^>^ get();
		void set(IDictionary<String^, WallTypeInfo^>^ value);
	};
};

}//namespace WallOpening

}//namespace MyDomain



