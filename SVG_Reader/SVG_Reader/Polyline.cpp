#include "Lib.h"

Polyline::Polyline() :Figure() {
	nVer = 0;
	Vers = NULL;
}

Polyline::~Polyline() {
	nVer = 0;
	if (Vers != NULL) {
		delete[] Vers;
		Vers = NULL;
	}
}

void Polyline::updateDiffElement() {
	string point = "";
	if (line.find("points") != string::npos)
		point = "points";

	int pos = line.find(point);
	line.erase(0, pos + point.size());

	for (int i = 0; i < line.size(); i++) {
		if (line[i] == ',')
			line[i] = ' ';
	}

	stringstream ss(line);
	string x, y;

	while (ss >> x >> y) {
		if (x[0] >= '0' && x[0] <= '9')
			nVer++;
		else break;
	}

	Vers = new Point[nVer];
	int i = 0;
	stringstream sss(line);

	while (sss >> x >> y) {
		if (x[0] >= '0' && x[0] <= '9') {
			Vers[i].setX(stof(x));
			Vers[i].setY(stof(y));
			i++;
		}
		else break;
	}
}

void Polyline::Draw(sf::RenderWindow& window) {
	Point end = Vers[nVer - 1];
	Point start = Vers[0];

	vector<Point> totalArray; //Contain point and itersect
	vector<Point> intersectArray;
	totalArray.push_back(Vers[0]); //Push back the first element of the vertices

	for (int i = 1; i < nVer; i++) {
		Point P1 = Vers[i - 1];
		Point P2 = Vers[i];
		Point intersect;

		if ((P1.getX() - P2.getX()) * (start.getY() - end.getY()) - (P1.getY() - P2.getY()) * (start.getX() - end.getX()) != 0) {
			intersect.setX(
				((P1.getX() * P2.getY() - P1.getY() * P2.getX()) * (start.getX() - end.getX()) - (P1.getX() - P2.getX()) * (start.getX() * end.getY() - start.getY() * end.getX())) * 1.0
				/ ((P1.getX() - P2.getX()) * (start.getY() - end.getY()) - (P1.getY() - P2.getY()) * (start.getX() - end.getX())));

			intersect.setY(((P1.getX() * P2.getY() - P1.getY() * P2.getX()) * (start.getY() - end.getY()) - (P1.getY() - P2.getY()) * (start.getX() * end.getY() - start.getY() * end.getX())) * 1.0
				/ ((P1.getX() - P2.getX()) * (start.getY() - end.getY()) - (P1.getY() - P2.getY()) * (start.getX() - end.getX())));
			intersect.setIntersect(true);

			if (intersectArray.empty()) {
				totalArray.push_back(intersect);
				intersectArray.push_back(intersect);
			}
			else {
				bool flag = false;
				for (auto point : intersectArray) {
					if ((point == intersect)) {
						flag = true;
						break;
					}
				}
				if (!flag) {
					intersectArray.push_back(intersect);
					totalArray.push_back(intersect);
				}
			}
		}
		totalArray.push_back(Vers[i]);
	}

	int pos = -1;
	for (int i = 0; i < totalArray.size(); i++) {
		if (totalArray[i].getIntersect()) {
			pos = i;
			break;
		}
	}
	int cnt = 0;

	for (int i = pos + 1; i < totalArray.size(); i++) {
		if (totalArray[i].getIntersect()) {
			cnt = cnt + 2;
			//Process
			sf::ConvexShape shape;
			shape.setPointCount(cnt);
			for (int k = 0; k < cnt; k++) 
				shape.setPoint(k, sf::Vector2f(totalArray[k + pos].getX(), totalArray[k + pos].getY()));

			if (colorProp.getFill().r != -1) {
				shape.setFillColor(sf::Color(colorProp.getFill().r, colorProp.getFill().g, colorProp.getFill().b));
				if (colorProp.getFillOpa() > 0) 
					shape.setFillColor(sf::Color(colorProp.getFill().r, colorProp.getFill().g, colorProp.getFill().b, colorProp.getFillOpa() * MAX));	
			}
			else {
				if (colorProp.getFillOpa() >= 0)
					shape.setFillColor(sf::Color(0, 0, 0, colorProp.getFillOpa() * MAX));
				else shape.setFillColor(sf::Color::Transparent);
			}
			window.draw(shape);
			pos = i;
			cnt = 0;
		}
		else ++cnt;
	}
	//Making the outline of the shape
	for (int i = 1; i < nVer; i++) {
		sf::ConvexShape rect;

		rect.setPointCount(4);
		rect.setPoint(0, sf::Vector2f(Vers[i].getX(), Vers[i].getY()));
		rect.setPoint(1, sf::Vector2f(Vers[i].getX(), Vers[i].getY()));
		rect.setPoint(2, sf::Vector2f(Vers[i - 1].getX(), Vers[i - 1].getY()));
		rect.setPoint(3, sf::Vector2f(Vers[i - 1].getX(), Vers[i - 1].getY()));

		if (colorProp.getStroke().r != -1) {
			rect.setOutlineColor(sf::Color(colorProp.getStroke().r, colorProp.getStroke().g, colorProp.getStroke().b));
			rect.setOutlineThickness(colorProp.getStrokeWidth() / 2);
			if (colorProp.getStrokeOpa() >= 0) 
				rect.setOutlineColor(sf::Color(colorProp.getStroke().r, colorProp.getStroke().g, colorProp.getStroke().b, colorProp.getStrokeOpa() * MAX));
			else rect.setOutlineColor(sf::Color::Transparent);
		}
		window.draw(rect);
	}
}