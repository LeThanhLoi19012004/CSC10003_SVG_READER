#include "Lib.h"

Rectangle::Rectangle() :Figure() {
	width = height = 0;
	root.setX(0);
	root.setY(0);
}

Rectangle::~Rectangle() {
	width = height = 0;
	root.setX(0);
	root.setY(0);
}

void Rectangle::updateProperty() {
	stringstream ss(line);
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

Point Rectangle::getRoot() {
	return this->root;
}

float Rectangle::getWidth() {
	return this->width;
}

float Rectangle::getHeight() {
	return this->height;
}

void Rectangle::setRoot(Point root) {
	this->root = root;
}

void Rectangle::setWidth(float w) {
	this->width = w;
}

void Rectangle::setHeight(float h) {
	this->height = h;
}

void Rectangle::transformFigure() {
	float curX = this->root.getX();
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
	}
}
