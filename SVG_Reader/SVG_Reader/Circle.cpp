#include "Lib.h"

CIRCLE::CIRCLE() :ELLIPSE() {
	this->setCenter(0, 0);
	this->setRx(0);
	this->setRy(0);
}

CIRCLE::~CIRCLE() {
	this->setCenter(0, 0);
	this->setRx(0);
	this->setRy(0);
}

void CIRCLE::updateProperty() {
	stringstream ss(line);
	string attribute, val, temp;

	while (ss >> attribute) {
		getline(ss, temp, '"');
		getline(ss, val, '"');
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