#include "Lib.h"

rectangle::rectangle() : figure() {
	width = height = 0;
	root.setX(0);
	root.setY(0);
}

rectangle::~rectangle() {
	width = height = 0;
	root.setX(0);
	root.setY(0);
}

void rectangle::updateProperty() {
	stringstream ss(line_str);
	string attribute, val, temp;

	while (ss >> attribute) {
		getline(ss, temp, '"');
		getline(ss, val, '"');

		if (attribute == "x")
			this->root.setX(stof(val));
		if (attribute == "y")
			this->root.setY(stof(val));
		if (attribute == "width")
			this->width = stof(val);
		if (attribute == "height")
			this->height = stof(val);
	}
}

point rectangle::getRoot() {
	return this->root;
}

float rectangle::getWidth() {
	return this->width;
}

float rectangle::getHeight() {
	return this->height;
}

void rectangle::setRoot(point root) {
	this->root = root;
}

void rectangle::setWidth(float w) {
	this->width = w;
}

void rectangle::setHeight(float h) {
	this->height = h;
}

void rectangle::transformFigure() {
	/*float curX = this->root.getX();
	float curY = this->root.getY();
	for (auto p : transVct) {
		if (p.first == "translate") {
			this->root.setX(curX + p.second[0]);
			this->root.setY(curY + p.second[1]);
		}
		if (p.first == "rotate") {
			this->isRotate = true;
		}
		if (p.first == "scale") {
			curX = this->root.getX();
			curY = this->root.getY();
			if (p.second.size() == 1) {
				float scl = p.second[0];
				this->root.setX(curX * scl);
				this->root.setY(curY * scl);
				this->width *= scl;
				this->height *= scl;
			}
			else {
				float sclX = p.second[0];
				float sclY = p.second[1];

				this->root.setX(curX * sclX);
				this->root.setY(curY * sclY);
				this->width *= sclX;
				this->height *= sclY;
			}
		}
	}*/
}
