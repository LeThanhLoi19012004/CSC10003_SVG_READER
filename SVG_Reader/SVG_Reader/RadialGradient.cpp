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