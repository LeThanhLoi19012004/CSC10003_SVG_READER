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
	
	if (colorProp.getFill().r != -1) {
		rect.setFillColor(sf::Color(colorProp.getFill().r, colorProp.getFill().g, colorProp.getFill().b));
		if (colorProp.getFillOpa() >= 0)
			rect.setFillColor(sf::Color(colorProp.getFill().r, colorProp.getFill().g, colorProp.getFill().b, colorProp.getFillOpa() * MAX));
	}
	else rect.setFillColor(sf::Color::Transparent);

	if (colorProp.getStroke().r != -1) {
		rect.setOutlineColor(sf::Color(colorProp.getStroke().r, colorProp.getStroke().g, colorProp.getStroke().b));
		rect.setOutlineThickness(colorProp.getStrokeWidth());
		if (colorProp.getStrokeOpa() >= 0) 
			rect.setOutlineColor(sf::Color(colorProp.getStroke().r, colorProp.getStroke().g, colorProp.getStroke().b, colorProp.getStrokeOpa() * MAX));
	}
	else rect.setOutlineColor(sf::Color::Transparent);

	rect.setPosition(root.getX(), root.getY());
	window.draw(rect);
}