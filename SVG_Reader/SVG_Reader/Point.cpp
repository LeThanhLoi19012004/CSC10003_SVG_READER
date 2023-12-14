#include "Lib.h"

point::point() {
	x = y = 0;
	intersect = false;
}

point::~point() {
	x = y = 0;
	intersect = false;
}

float point::getX() {
	return this->x;
}

float point::getY() {
	return this->y;
}

bool point::getIntersect() {
	return this->intersect;
}

void point::setIntersect(bool intersect) {
	this->intersect = intersect;
}

void point::setX(float x) {
	this->x = x;
}

void point::setY(float y) {
	this->y = y;
}

bool operator == (const point& p1, const point& p2) {
	return p1.x == p2.x && p1.y == p2.y;
}