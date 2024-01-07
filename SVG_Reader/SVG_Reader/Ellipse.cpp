#include "Lib.h"

ellipse::ellipse() : figure() {
	rx = ry = 0;
	center.setX(0);
	center.setY(0);
}

ellipse::~ellipse() {
	rx = ry = 0;
	center.setX(0);
	center.setY(0);
}

void ellipse::updateProperty() {
	stringstream ss(line_str);
	string property, val, temp;

	while (ss >> property) {
		getline(ss, temp, '"');
		getline(ss, val, '"');

		if (property == "rx")
			this->rx = stof(val);
		if (property == "ry")
			this->ry = stof(val);
		if (property == "cx")
			this->center.setX(stof(val));
		if (property == "cy")
			this->center.setY(stof(val));
	}
}

point ellipse::getCenter() {
	return this->center;
}

float ellipse::getRx() {
	return this->rx;
}

float ellipse::getRy() {
	return this->ry;
}

void ellipse::setCenter(float x, float y) {
	this->center.setX(x);
	this->center.setY(y);
}

void ellipse::setRx(float rx) {
	this->rx = rx;
}

void ellipse::setRy(float ry) {
	this->ry = ry;
}