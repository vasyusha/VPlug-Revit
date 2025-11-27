#pragma once

#include "BaseElement.h"

using namespace System;
using namespace System::Collections::Generic;

namespace Elements {

public ref class WallElement : BaseElement {
private:
	double area_;
	bool hasOpening_;
	int countOpening_;

	/*Логические дочерние элементы, включая FindInserts(addRectOpenings, includeShadows)*/
	IList<BaseElement^>^ logicChildren_;

public:

	property double Area {
		double get();
		void set(double value);
	};

	property bool HasOpening {
		bool get();
		void set(bool value);
	};

	property int CountOpening {
		int get();
		void set(int value);
	};

	property IList<BaseElement^>^ LogicChildren {
		IList<BaseElement^>^ get();
		void set(IList<BaseElement^>^ value);
	};
};

}//namespace Elements