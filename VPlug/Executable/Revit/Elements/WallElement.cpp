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

int WallElement::CountOpening::get() {
	return countOpening_;
}

void WallElement::CountOpening::set(int value) {
	countOpening_ = value;
}

IList<BaseElement^>^ WallElement::LogicChildren::get() {
	return logicChildren_;
}

void WallElement::LogicChildren::set(IList<BaseElement^>^ value) {
	logicChildren_ = value;
}

}//namespace Elements