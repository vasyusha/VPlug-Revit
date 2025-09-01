#pragma once
#include "BaseElement.h"

namespace Elements {

public ref class WallElement : public BaseElement {
private:
	double area_;
	bool has_opening_;

public:
	void SetArea(double area);
	double GetArea();

	void SetHasOpening(bool has_onening);
	bool GetHasOpening();
};

}