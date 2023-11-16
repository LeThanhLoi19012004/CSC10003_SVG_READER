#include "Lib.h"

Line::Line() :Figure() {
	p1.setX(0); p1.setY(0);
	p2.setX(0); p2.setY(0);
}
Line::~Line() {
	p1.setX(0); p1.setY(0);
	p2.setX(0); p2.setY(0);
}

void Line::updateDiffElement()
{
	stringstream ss(line);
	string attribute, val;

	while (ss >> attribute >> val) {
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

Point Line::getP1() {
	return this->p1;
}

Point Line::getP2() {
	return this->p2;
}

void Line::setP1(Point p1) {
	this->p1 = p1;
}

void Line::setP2(Point p2) {
	this->p2 = p2;
}

void Line::Draw(sf::RenderWindow& window) {

	sf::ConvexShape line;

	line.setPointCount(4);
	line.setPoint(0, sf::Vector2f(p1.getX(), p1.getY()));
	line.setPoint(1, sf::Vector2f(p1.getX(), p1.getY()));
	line.setPoint(2, sf::Vector2f(p2.getX(), p2.getY()));
	line.setPoint(3, sf::Vector2f(p2.getX(), p2.getY()));

	if (colorProp.getStroke().r != -1) {
		line.setOutlineColor(sf::Color(colorProp.getStroke().r, colorProp.getStroke().g, colorProp.getStroke().b));
		line.setOutlineThickness(colorProp.getStrokeWidth() / 2);
		if (colorProp.getStrokeOpa() >= 0) 
			line.setOutlineColor(sf::Color(colorProp.getStroke().r, colorProp.getStroke().g, colorProp.getStroke().b, colorProp.getStrokeOpa() * MAX));
	}
	else line.setOutlineColor(sf::Color::Transparent);
	window.draw(line);
}