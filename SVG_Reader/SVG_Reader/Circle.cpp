#include "Lib.h"

Circle::Circle() :Ellipse() {
	this->setCenter(0, 0);
	this->setRx(0);
	this->setRy(0);
}

Circle::~Circle() {
	this->setCenter(0, 0);
	this->setRx(0);
	this->setRy(0);
}

void Circle::updateDiffElement() {
	stringstream ss(line);
	string attribute, val;

	while (ss >> attribute >> val) {
		if (attribute == "r") {
			this->setRx(stof(val));
			this->setRy(stof(val));
		}
		if (attribute == "cx")
			this->center.setX((stof(val)));
		if (attribute == "cy")
			this->center.setY((stof(val)));
	}
}