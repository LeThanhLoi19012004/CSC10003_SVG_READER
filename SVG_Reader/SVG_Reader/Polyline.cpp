#include "Lib.h"

polyline::polyline() :figure() {
	Vers = {};
}

polyline::~polyline() {
	Vers = {};
}

void polyline::updateProperty() {
	stringstream ss(line_str);
	string property, val, temp;

	while (ss >> property) {
		getline(ss, temp, '"');
		getline(ss, val, '"');
		if (property == "points" || property == "point") {
			for (int i = 0; i < val.size(); i++)
				if (val[i] == ',' || val[i] == '/')
					val[i] = ' ';

			stringstream ss(val);
			string x = "", y = "";
			while (ss >> x >> y) {
				point p;
				p.setX(stof(x));
				p.setY(stof(y));
				Vers.push_back(p);
			}
			/*Vers = new point[nVer];
			int i = 0;

			stringstream pointLine(val);
			while (pointLine >> x >> y) {
				Vers[i].setX(stof(x));
				Vers[i].setY(stof(y));
				i++;
			}*/
		}
	}
}

vector<point> polyline::getVers() {
	return this->Vers;
}

void polyline::setVers(vector<point> Vers) {
	this->Vers = Vers;
}

void polyline::transformFigure() {
	/*for (int i = 0; i < nVer; i++) {
		float curX = this->Vers[i].getX();
		float curY = this->Vers[i].getY();
		for (auto p : transVct) {
			if (p.first == "translate") {
				this->Vers[i].setX(curX + p.second[0]);
				this->Vers[i].setY(curY + p.second[1]);
			}
			if (p.first == "rotate") {
				this->isRotate = true;

				float A = cos(p.second[0] * Pi / 180.f);
				float B = sin(p.second[0] * Pi / 180.f);
				curX = (this->Vers[i].getX() * A - this->Vers[i].getY() * B);
				curY = (this->Vers[i].getX() * B + this->Vers[i].getY() * A);
				this->Vers[i].setX(curX);
				this->Vers[i].setY(curY);
			}
			if (p.first == "scale") {
				curX = this->Vers[i].getX();
				curY = this->Vers[i].getY();
				if (p.second.size() == 1) {
					float scl = p.second[0];
					this->Vers[i].setX(curX * scl);
					this->Vers[i].setY(curY * scl);
				}
				else {
					float sclX = p.second[0];
					float sclY = p.second[1];

					this->Vers[i].setX(curX * sclX);
					this->Vers[i].setY(curY * sclY);

				}
			}
		}

	}*/
}