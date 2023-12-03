#include "Lib.h"

POINT::POINT() {
	x = y = 0;
	intersect = false;
}

POINT::~POINT() {
	x = y = 0;
	intersect = false;
}

float POINT::getX() {
	return this->x;
}

float POINT::getY() {
	return this->y;
}

bool POINT::getIntersect() {
	return this->intersect;
}

void POINT::setIntersect(bool intersect) {
	this->intersect = intersect;
}

void POINT::setX(float x) {
	this->x = x;
}

void POINT::setY(float y) {
	this->y = y;
}

bool operator == (const POINT& p1, const POINT& p2) {
	return p1.x == p2.x && p1.y == p2.y;
}