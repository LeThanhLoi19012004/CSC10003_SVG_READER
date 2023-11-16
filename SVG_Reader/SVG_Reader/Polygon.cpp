#include "Lib.h"

Polygon::Polygon() : Figure() {
	nVer = 0;
	Vers = NULL;
}

Polygon::~Polygon() {
	nVer = 0;
	if (Vers != NULL)
		delete[] Vers;
}

void Polygon::updateDiffElement() {
	string point = "";
	if (line.find("points") != string::npos)
		point = "points";

	int pos = line.find(point);
	line.erase(0, pos + point.size());

	for (int i = 0; i < line.size(); i++)
		if (line[i] == ',')
			line[i] = ' ';

	stringstream ss(line);
	string x = "", y = "";
	while (ss >> x >> y)
		nVer++;

	Vers = new Point[nVer];
	int i = 0;

	stringstream pointLine(line);
	while (pointLine >> x >> y) {
		Vers[i].setX(stof(x));
		Vers[i].setY(stof(y));
		i++;
	}
}

void Polygon::Draw(sf::RenderWindow& window) {
	sf::ConvexShape polygon;
	polygon.setPointCount(nVer);

	for (int i = 0; i < nVer; i++)
		polygon.setPoint(i, sf::Vector2f(Vers[i].getX(), Vers[i].getY()));

	if (fill.r != -1) {
		polygon.setFillColor(sf::Color(fill.r, fill.g, fill.b));
		if (fill.opacity >= 0)
			polygon.setFillColor(sf::Color(fill.r, fill.g, fill.b, fill.opacity * MAX));
	}
	else polygon.setFillColor(sf::Color::Transparent);

	if (stroke.getStrokeColor().r != -1) {
		polygon.setOutlineColor(sf::Color(stroke.getStrokeColor().r, stroke.getStrokeColor().g, stroke.getStrokeColor().b));
		polygon.setOutlineThickness(stroke.getStrokeWidth());
		if (stroke.getStrokeColor().opacity >= 0)
			polygon.setOutlineColor(sf::Color(stroke.getStrokeColor().r, stroke.getStrokeColor().g, stroke.getStrokeColor().b, stroke.getStrokeColor().opacity * MAX));
	}
	else polygon.setOutlineColor(sf::Color::Transparent);
	window.draw(polygon);
}