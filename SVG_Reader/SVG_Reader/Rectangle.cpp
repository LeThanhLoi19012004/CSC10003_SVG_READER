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

void Rectangle::updateDiffElement() {
	stringstream ss(line);
	string attribute, val;

	while (ss >> attribute >> val) {
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

void Rectangle::Draw(sf::RenderWindow& window) {
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(width, height));

	if (fill.r != -1) {
		rect.setFillColor(sf::Color(fill.r, fill.g, fill.b));
		if (fill.opacity >= 0)
			rect.setFillColor(sf::Color(fill.r, fill.g, fill.b, fill.opacity * MAX));
	}
	else rect.setFillColor(sf::Color::Transparent);

	if (stroke.getStrokeColor().r != -1) {
		rect.setOutlineColor(sf::Color(stroke.getStrokeColor().r, stroke.getStrokeColor().g, stroke.getStrokeColor().b));
		rect.setOutlineThickness(stroke.getStrokeWidth());
		if (stroke.getStrokeColor().opacity >= 0)
			rect.setOutlineColor(sf::Color(stroke.getStrokeColor().r, stroke.getStrokeColor().g, stroke.getStrokeColor().b, stroke.getStrokeColor().opacity * MAX));
	}
	else rect.setOutlineColor(sf::Color::Transparent);

	rect.setPosition(root.getX(), root.getY());
	window.draw(rect);
}