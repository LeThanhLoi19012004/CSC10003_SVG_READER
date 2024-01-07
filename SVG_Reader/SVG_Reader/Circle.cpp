#include "Lib.h"

circle::circle() : ellipse() {
	this->setCenter(0, 0);
	this->setRx(0);
	this->setRy(0);
}

circle::~circle() {
	this->setCenter(0, 0);
	this->setRx(0);
	this->setRy(0);
}

void circle::updateProperty() {
	stringstream ss(line_str);
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