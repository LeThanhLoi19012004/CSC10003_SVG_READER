#include "Lib.h"

Stroke::Stroke() {
	this->strokeWidth = 0;
}

Stroke::~Stroke() {
	this->strokeWidth = 0;
}

COLOR Stroke::getStrokeColor() {
	return this->strokeColor;
}

float Stroke::getStrokeWidth() {
	return this->strokeWidth;
}

void Stroke::setStrokeColor(COLOR strokeColor) {
	this->strokeColor = strokeColor;
}

void Stroke::setStrokeWidth(float strokeWidth) {
	this->strokeWidth = strokeWidth;
}