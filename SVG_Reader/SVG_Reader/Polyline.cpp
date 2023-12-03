#include "Lib.h"

polyline::polyline() :figure() {
	nVer = 0;
	Vers = NULL;
}

polyline::~polyline() {
	nVer = 0;
	if (Vers != NULL) {
		delete[] Vers;
		Vers = NULL;
	}
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
			while (ss >> x >> y)
				nVer++;

			Vers = new point[nVer];
			int i = 0;

			stringstream pointLine(val);
			while (pointLine >> x >> y) {
				Vers[i].setX(stof(x));
				Vers[i].setY(stof(y));
				i++;
			}
		}
	}
}

point* polyline::getVers() {
	return this->Vers;
}
int polyline::getNVer() {
	return this->nVer;
}

void polyline::setVers(point* Vers) {
	if (this->Vers != NULL) {
		delete[] Vers;
		Vers = NULL;
		this->Vers = Vers;
	}
}
void polyline::setNVer(int nVer) {
	this->nVer = nVer;
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