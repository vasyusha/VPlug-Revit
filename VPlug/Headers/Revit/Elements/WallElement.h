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
};

}//namespace Elements