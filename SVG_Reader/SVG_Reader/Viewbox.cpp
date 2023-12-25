#include "Lib.h"

float viewbox::getViewX() {
	return this->viewX;
}

float viewbox::getViewY() {
	return this->viewY;
}

float viewbox::getViewWidth() {
	return this->viewWidth;
}

float viewbox::getViewHeight() {
	return this->viewHeight;
}

float viewbox::getPortWidth() {
	return this->portWidth;
}

float viewbox::getPortHeight() {
	return this->portHeight;
}
string viewbox::getPreservedForm() {
	return this->preservedForm;
}

string viewbox::getPreservedMode() {
	return this->preservedMode;
}

void viewbox::setPortWidth(float portWidth) {
	this->portWidth = portWidth;
}

void viewbox::setPortHeight(float portHeight) {
	this->portHeight = portHeight;
}

void viewbox::setPreservedMode(string mode) {
	this->preservedMode = mode;
}

void viewbox::setPreservedForm(string form) {
	this->preservedForm = form;
}

void viewbox::setViewWidth(float width) {
	this->viewWidth = width;
}

void viewbox::setViewHeight(float height) {
	this->viewHeight = height;
}

void viewbox::setViewX(float X) {
	this->viewX = X;
}

void viewbox::setViewY(float Y) {
	this->viewY = Y;
}