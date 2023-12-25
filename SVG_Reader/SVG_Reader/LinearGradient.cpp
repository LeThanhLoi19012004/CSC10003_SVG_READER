#include "Lib.h"

color stop::getStopColor() {
	return this->stopColor;
}
float stop:: getStopOpa() {
	return this->stopOpa;
}
float stop:: getOffSet() {
	return this->offset;
}

void stop::setStopColor(color stopColor) {
	this->stopColor = stopColor;
}
void stop:: setStopOpa(float opa) {
	this->stopOpa = opa;
}
void stop:: setOffSet(float offSet) {
	this->offset = offset;
}

vector<stop> lineargradient::getStopVct() {
	return this->stopVct;
}
float lineargradient::getX1() {
	return this->x1;
}
float lineargradient:: getY1() {
	return this->y1;
}
float lineargradient:: getX2() {
	return this->x2;
}
float lineargradient:: getY2() {
	return this->y2;
}

void lineargradient::setX1(float x1) {
	this->x1 = x1;
}
void lineargradient::setY1(float y1) {
	this->y1 = y1;
}
void lineargradient::setX2(float x2) {
	this->x2 = x2;
}
void lineargradient::setY2(float y2) {
	this->y2 = y2;
}