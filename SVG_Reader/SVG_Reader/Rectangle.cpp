#include "Lib.h"

rectangle::rectangle() : figure() {
	width = height = 0;
	root.setX(0);
	root.setY(0);
}

rectangle::~rectangle() {
	width = height = 0;
	root.setX(0);
	root.setY(0);
}

void rectangle::updateProperty() {
	stringstream ss(line_str);
	string attribute, val, temp;

	while (ss >> attribute) {
		getline(ss, temp, '"');
		getline(ss, val, '"');

		if (attribute == "x")
			this->root.setX(stof(val));
		if (attribute == "y")
			this->root.setY(stof(val));
		if (attribute == "width")
			this->width = stof(val);
		if (attribute == "height")
			this->height = stof(val);
	}
}

point rectangle::getRoot() {
	return this->root;
}

float rectangle::getWidth() {
	return this->width;
}

float rectangle::getHeight() {
	return this->height;
}

void rectangle::setRoot(point root) {
	this->root = root;
}

void rectangle::setWidth(float w) {
	this->width = w;
}

void rectangle::setHeight(float h) {
	this->height = h;
}