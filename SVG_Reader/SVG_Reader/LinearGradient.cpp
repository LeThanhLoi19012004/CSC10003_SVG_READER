#include "Lib.h"

point lineargradient::getA() {
	return A;
}

point lineargradient::getB() {
	return B;
}

void lineargradient::setA(point p) {
	this->A = p;
}

void lineargradient::setB(point p) {
	this->B = p;
}

lineargradient::lineargradient() {
	A.setX(0);
	A.setY(0);
	B.setX(0);
	B.setY(0);
}

lineargradient::lineargradient(const lineargradient& linear) {
	this->A = linear.A;
	this->B = linear.B;

}

lineargradient& lineargradient::operator=(const lineargradient& linear) {
	if (this != &linear) {
		this->A = linear.A;
		this->B = linear.B;
	}
	return *this;
}

void lineargradient::updateElement() {
	stringstream sss(strLine);
	string temp = "", attribute = "", value = "", transformGradient = "";

	while (sss >> attribute) {
		getline(sss, temp, '"');
		getline(sss, value, '"');

		if (attribute == "x1") {
			A.setX(stof(value));
		}
		if (attribute == "y1") {
			A.setY(stof(value));
		}
		if (attribute == "x2") {
			B.setX(stof(value));
		}
		if (attribute == "y2") {
			B.setY(stof(value));
		}
		if (attribute == "gradientTransform") {
			transformGradient = value;
		}
	}
	this->updateGradientTransform(transformGradient);
}