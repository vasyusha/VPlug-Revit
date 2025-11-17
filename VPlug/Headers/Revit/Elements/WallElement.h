#pragma once

#include "BaseElement.h"

using namespace System;
using namespace System::Collections::Generic;

namespace Elements {

public ref class WallElement : BaseElement {
private:
	double area_;
	bool hasOpening_;

public:

	property double Area {
		double get();
		void set(double value);
	};

	property bool HasOpening {
		bool get();
		void set(bool value);
	};
};

}//namespace Elements