#include "Lib.h"

line::line() :figure() {
	p1.setX(0); p1.setY(0);
	p2.setX(0); p2.setY(0);
}
line::~line() {
	p1.setX(0); p1.setY(0);
	p2.setX(0); p2.setY(0);
}

void line::updateProperty()
{
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

void line::transformFigure() {
	/*float curX1 = this->p1.getX();
	float curY1 = this->p1.getY();

	float curX2 = this->p2.getX();
	float curY2 = this->p2.getY();

	for (auto p : transVct) {
		if (p.first == "translate") {
			this->p1.setX(curX1 + p.second[0]);
			this->p1.setY(curY1 + p.second[1]);

			this->p2.setX(curX2 + p.second[0]);
			this->p2.setY(curY2 + p.second[1]);
		}
		if (p.first == "rotate") {
			this->isRotate = true;
		}
		if (p.first == "scale") {
			curX1 = this->p1.getX();
			curY1 = this->p1.getY();
			curX2 = this->p2.getX();
			curY2 = this->p2.getY();
			if (p.second.size() == 1) {
				float scl = p.second[0];
				this->p1.setX(curX1 * scl);
				this->p1.setY(curY1 * scl);

				this->p2.setX(curX2 * scl);
				this->p2.setY(curY2 * scl);
			}
			else {
				float sclX = p.second[0];
				float sclY = p.second[1];

				this->p1.setX(curX1 * sclX);
				this->p1.setY(curY1 * sclY);

				this->p2.setX(curX2 * sclX);
				this->p2.setY(curY2 * sclY);
			}
		}
	}*/
}