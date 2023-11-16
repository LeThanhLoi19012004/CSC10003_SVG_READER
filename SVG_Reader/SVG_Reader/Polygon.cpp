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

	if (colorProp.getFill().r != -1) {
		polygon.setFillColor(sf::Color(colorProp.getFill().r, colorProp.getFill().g, colorProp.getFill().b));
		if (colorProp.getFillOpa() > 0)
			polygon.setFillColor(sf::Color(colorProp.getFill().r, colorProp.getFill().g, colorProp.getFill().b, colorProp.getFillOpa() * MAX));
	}
	else polygon.setFillColor(sf::Color::Transparent);

	if (colorProp.getStroke().r != -1) {
		polygon.setOutlineColor(sf::Color(colorProp.getStroke().r, colorProp.getStroke().g, colorProp.getStroke().b));
		polygon.setOutlineThickness(colorProp.getStrokeWidth());
		if (colorProp.getStrokeOpa() > 0)
			polygon.setOutlineColor(sf::Color(colorProp.getStroke().r, colorProp.getStroke().g, colorProp.getStroke().b, colorProp.getStrokeOpa() * MAX));
	}
	else polygon.setOutlineColor(sf::Color::Transparent);

	window.draw(polygon);
}