#include "Lib.h"

stroke::stroke() {
	this->strokeWidth = 1;
}

stroke::~stroke() {
	this->strokeWidth = 0;
}

color stroke::getStrokeColor() {
	return this->strokeColor;
}

float stroke::getStrokeWidth() {
	return this->strokeWidth;
}

void stroke::setStrokeColor(color strokeColor) {
	this->strokeColor = strokeColor;
}

void stroke::setStrokeWidth(float strokeWidth) {
	this->strokeWidth = strokeWidth;
}