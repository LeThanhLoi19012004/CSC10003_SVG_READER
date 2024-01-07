#include "Lib.h"

line::line() :figure() {
	p1.setX(0); p1.setY(0);
	p2.setX(0); p2.setY(0);
}

line::~line() {
	p1.setX(0); p1.setY(0);
	p2.setX(0); p2.setY(0);
}

void line::updateProperty(){
	stringstream ss(line_str);
	string attribute, val, temp;

	while (ss >> attribute) {
		getline(ss, temp, '"');
		getline(ss, val, '"');

		if (attribute == "x1") {
			this->p1.setX(stof(val));
		}
		if (attribute == "y1") {
			this->p1.setY(stof(val));
		}
		if (attribute == "x2") {
			this->p2.setX(stof(val));
		}
		if (attribute == "y2") {
			this->p2.setY(stof(val));
		}
	}
}

point line::getP1() {
	return this->p1;
}

point line::getP2() {
	return this->p2;
}

void line::setP1(point p1) {
	this->p1 = p1;
}

void line::setP2(point p2) {
	this->p2 = p2;
}