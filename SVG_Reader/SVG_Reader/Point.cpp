#include "Lib.h"

Point::Point() {
	x = y = 0;
	intersect = false;
}

Point::~Point() {
	x = y = 0;
	intersect = false;
}

float Point::getX() {
	return this->x;
}

float Point::getY() {
	return this->y;
}

bool Point::getIntersect() {
	return this->intersect;
}

void Point::setIntersect(bool intersect) {
	this->intersect = intersect;
}

void Point::setX(float x) {
	this->x = x;
}

void Point::setY(float y) {
	this->y = y;
}

bool operator == (const Point& p1, const Point& p2) {
	return p1.x == p2.x && p1.y == p2.y;
}