#include "..\..\..\Headlines\Revit\Elements\WallElement.h"

void Elements::WallElement::SetArea(double area) {
	area_ = area;
}
double Elements::WallElement::GetArea() {
	return area_;
}

void Elements::WallElement::SetHasOpening(bool has_opening) {
	has_opening_ = has_opening;
}
bool Elements::WallElement::GetHasOpening() {
	return has_opening_;
}