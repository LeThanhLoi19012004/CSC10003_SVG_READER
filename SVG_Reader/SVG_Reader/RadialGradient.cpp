#include "Lib.h"

float radialgradient::getCx() {
	return cx;
}
float radialgradient::getCy() {
	return cy;
}
float radialgradient::getR() {
	return r;
}
float radialgradient::getFx() {
	return fx;
}
float radialgradient::getFy() {
	return fy;
}

radialgradient::radialgradient() {
	isLink = false;
	cx = cy = r = fx = fy = 0;
}

radialgradient::radialgradient(const radialgradient& radial) {
	cx = radial.cx;
	cy = radial.cy;
	r = radial.r;
	fx = radial.fx;
	fy = radial.fy;
}
radialgradient& radialgradient::operator = (const radialgradient& radial) {
	if (this != &radial) {
		cx = radial.cx;
		cy = radial.cy;
		r = radial.r;
		fx = radial.fx;
		fy = radial.fy;
	}
	return *this;
}

void radialgradient::updateElement() {
	stringstream sss(strLine);
	string temp = "", attribute = "", value = "", transformGradient = "";

	while (sss >> attribute) {
		getline(sss, temp, '"');
		getline(sss, value, '"');

		if (attribute == "cx") {
			this->cx = stof(value);
		}
		if (attribute == "cy") {
			this->cy = stof(value);
		}
		if (attribute == "r") {
			this->r = stof(value);
		}
		if (attribute == "fx") {
			this->fx = stof(value);
		}
		if (attribute == "fy") {
			this->fy = stof(value);
		}
		if (attribute == "gradientTransform") {
			transformGradient = value;
		}
		if (attribute == "xlink:href") {
			this->isLink = true;
		}
	}
	this->updateGradientTransform(transformGradient);
}

bool radialgradient::getIsLink() {
	return this->isLink;
}

void radialgradient::setIsLink(bool link) {
	this->isLink = link;
}