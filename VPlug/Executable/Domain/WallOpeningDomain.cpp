#include "../../Headers/Domain/WallOpeningDomain.h"

namespace MyDomain {

namespace WallOpening {

int OpeningInfo::Id::get() {
	return id_;
}

void OpeningInfo::Id::set(int value) {
	id_ = value;
}

String^ OpeningInfo::Name::get() {
	return name_;
}

void OpeningInfo::Name::set(String^ value) {
	name_ = value;
}

String^ OpeningInfo::CategoryName::get() {
	return categoryName_;
}

void OpeningInfo::CategoryName::set(String^ value) {
	categoryName_ = value;
}

WallElementInfo::WallElementInfo() {
	openings_ = gcnew List<OpeningInfo^>();
}

int WallElementInfo::Id::get() {
	return id_;
}

void WallElementInfo::Id::set(int value) {
	id_ = value;
}

String^ WallElementInfo::Name::get() {
	return name_;
}

void WallElementInfo::Name::set(String^ value) {
	name_ = value;
}

String^ WallElementInfo::CategoryName::get() {
	return categoryName_;
}

void WallElementInfo::CategoryName::set(String^ value) {
	categoryName_ = value;
}

double WallElementInfo::Area::get() {
	return area_;
}

void WallElementInfo::Area::set(double value) {
	area_ = value;
}

int WallElementInfo::CountOpenings::get() {
	return countOpenings_;
}

void WallElementInfo::CountOpenings::set(int value) {
	countOpenings_ = value;
}

IList<OpeningInfo^>^ WallElementInfo::Openings::get() {
	return openings_;
}

void WallElementInfo::Openings::set(IList<OpeningInfo^>^ value) {
	openings_ = value;
}

WallTypeInfo::WallTypeInfo() {
	openings_ = gcnew List<OpeningInfo^>();
}

String^ WallTypeInfo::Name::get() {
	return name_;
}

void WallTypeInfo::Name::set(String^ value) {
	name_ = value;
}

int WallTypeInfo::TotalWalls::get() {
	return totalWalls_;
}

void WallTypeInfo::TotalWalls::set(int value) {
	totalWalls_ = value;
}

double WallTypeInfo::TotalArea::get() {
	return totalArea_;
}

void WallTypeInfo::TotalArea::set(double value) {
	totalArea_ = value;
}

int WallTypeInfo::TotalOpenings::get() {
	return totalOpenings_;
}

void WallTypeInfo::TotalOpenings::set(int value) {
	totalOpenings_ = value;
}

double WallTypeInfo::TotalAreaWallsWithOpenings::get() {
	return totalAreaWallsWithOpenings_;
}

void WallTypeInfo::TotalAreaWallsWithOpenings::set(double value) {
	totalAreaWallsWithOpenings_ = value;
}

double WallTypeInfo::TotalAreaWallsWithoutOpenings::get() {
	return totalAreaWallsWithoutOpenings_;
}

void WallTypeInfo::TotalAreaWallsWithoutOpenings::set(double value) {
	totalAreaWallsWithoutOpenings_ = value;
}

IList<OpeningInfo^>^ WallTypeInfo::Openings::get() {
	return openings_;
}

void WallTypeInfo::Openings::set(IList<OpeningInfo^>^ value) {
	openings_ = value;
}

WallOpeningReport::WallOpeningReport() {
	wallElements_ = gcnew List<WallElementInfo^>();
	wallTypes_ = gcnew Dictionary<String^, WallTypeInfo^>();
}

String^ WallOpeningReport::ProjectName::get() {
	return projectName_;
}

void WallOpeningReport::ProjectName::set(String^ value) {
	projectName_ = value;
}

String^ WallOpeningReport::DateTimeStr::get() {
	return dateTimeStr_;
}

void WallOpeningReport::DateTimeStr::set(String^ value) {
	dateTimeStr_ = value;
}

IList<WallElementInfo^>^ WallOpeningReport::WallElemnts::get() {
	return wallElements_;
}

void WallOpeningReport::WallElemnts::set(IList<WallElementInfo^>^ value) {
	wallElements_ = value;
}

IDictionary<String^, WallTypeInfo^>^ WallOpeningReport::WallTypes::get() {
	return wallTypes_;
}

void WallOpeningReport::WallTypes::set(IDictionary<String^, WallTypeInfo^>^ value) {
	wallTypes_ = value;
}

}//namespace WallOpening

}//namespace MyDomain
