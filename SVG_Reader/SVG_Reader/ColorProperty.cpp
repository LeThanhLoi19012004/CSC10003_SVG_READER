#include "Lib.h"

Color ColorProperty::getStroke() {
	return this->stroke;
}

Color ColorProperty::getFill() {
	return this->fill;
}

float ColorProperty::getFillOpa() {
	return this->fillOpa;
}

float ColorProperty::getStrokeOpa() {
	return this->strokeOpa;
}

float ColorProperty::getStrokeWidth() {
	return this->strokeWidth;
}

void ColorProperty::setStroke(Color stroke) {
	this->stroke.r = stroke.r;
	this->stroke.g = stroke.g;
	this->stroke.b = stroke.b;
}

void ColorProperty::setFill(Color fill) {
	this->fill.r = fill.r;
	this->fill.g = fill.g;
	this->fill.b = fill.b;
}

void ColorProperty::setFillOpa(float fillOpa) {
	this->fillOpa = fillOpa;
}

void ColorProperty::setStrokeWidth(float strokeWidth) {
	this->strokeWidth = strokeWidth;
}

void ColorProperty::setStrokeOpa(float strokeOpa) {
	this->strokeOpa = strokeOpa;
}