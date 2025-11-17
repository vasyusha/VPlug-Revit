#include "..\..\..\Headers\Revit\Elements\WallElement.h"

namespace Elements {

double WallElement::Area::get() {
	return area_;
}

void WallElement::Area::set(double value) {
	area_ = value;
}

bool WallElement::HasOpening::get() {
	return hasOpening_;
}

void WallElement::HasOpening::set(bool value) {
	hasOpening_ = value;
}

}//namespace Elements