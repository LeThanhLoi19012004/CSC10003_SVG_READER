#include "Lib.h"

ELLIPSE::ELLIPSE() :Figure() {
	rx = ry = 0;
	center.setX(0);
	center.setY(0);
}

ELLIPSE::~ELLIPSE() {
	rx = ry = 0;
	center.setX(0);
	center.setY(0);
}

void ELLIPSE::updateProperty() {
	stringstream ss(line);
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

POINT ELLIPSE::getCenter() {
	return this->center;
}

float ELLIPSE::getRx() {
	return this->rx;
}

float ELLIPSE::getRy() {
	return this->ry;
}

void ELLIPSE::setCenter(float x, float y) {
	this->center.setX(x);
	this->center.setY(y);
}

void ELLIPSE::setRx(float rx) {
	this->rx = rx;
}

void ELLIPSE::setRy(float ry) {
	this->ry = ry;
}

void ELLIPSE::transformFigure() {
	/*float curX = this->center.getX();
	float curY = this->center.getY();
	for (auto p : transVct) {
		if (p.first == "translate") {
			this->center.setX(curX + p.second[0]);
			this->center.setY(curY + p.second[1]);
		}
		if (p.first == "rotate") {
			this->isRotate = true;
		}
		if (p.first == "scale") {
			curX = this->center.getX();
			curY = this->center.getY();
			if (p.second.size() == 1) {
				float scl = p.second[0];
				this->center.setX(curX * scl);
				this->center.setY(curY * scl);
				this->rx *= scl;
				this->ry *= scl;
			}
			else {
				float sclX = p.second[0];
				float sclY = p.second[1];

				this->center.setX(curX * sclX);
				this->center.setY(curY * sclY);
				this->rx *= sclX;
				this->ry *= sclY;
			}
		}
	}*/
}

