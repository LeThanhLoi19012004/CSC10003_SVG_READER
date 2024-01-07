#include "Lib.h"

float viewbox::getViewX() const { 
	return viewX; 
}

float viewbox::getViewY() const {
	return viewY;
}

float viewbox::getViewWidth() const {
	return viewWidth;
}

float viewbox::getViewHeight() const { 
	return viewHeight; 
}

float viewbox::getPortWidth() const { 
	return portWidth; 
}

float viewbox::getPortHeight() const {
	return portHeight; 
}

const string& viewbox::getPreservedForm() const { 
	return preservedForm; 
}

const string& viewbox::getPreservedMode() const { 
	return preservedMode; 
}

void viewbox::setViewX(float value) { 
	viewX = value; 
}

void viewbox::setViewY(float value) { 
	viewY = value; 
}

void viewbox::setViewWidth(float value) { 
	viewWidth = value; 
}

void viewbox::setViewHeight(float value) { 
	viewHeight = value; 
}

void viewbox::setPortWidth(float value) { 
	portWidth = value; 
}

void viewbox::setPortHeight(float value) { 
	portHeight = value; 
}

void viewbox::setPreservedForm(const string& value) { 
	preservedForm = value; 
}

void viewbox::setPreservedMode(const string& value) { 
	preservedMode = value; 
}