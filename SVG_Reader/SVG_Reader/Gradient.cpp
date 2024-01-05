#include "Lib.h"

vector<stop> gradient::getStopVct() {
	return this->stopVct;
}

void gradient::setStopVct(vector<stop> vct) {
	this->stopVct = vct;
}

int gradient::getGradId() {
	return this->gradId;
}
void gradient::setGradId(int gradId) {
	this->gradId = gradId;
}
void gradient::addStop(stop stp) {
	stopVct.push_back(stp);
}

gradient::gradient() {
	stopVct = {};
}
gradient::gradient(const gradient& grad) {
	for (int i = 0; i < stopVct.size(); i++) {
		stopVct[i] = grad.stopVct[i];
	}
}
gradient& gradient::operator = (const gradient& grad) {
	if (this != &grad) {
		for (int i = 0; i < stopVct.size(); i++) {
			stopVct[i] = grad.stopVct[i];
		}
	}
	return *this;
}