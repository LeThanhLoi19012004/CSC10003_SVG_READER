#include "Lib.h"

polyline::polyline() :figure() {
	fill.r = fill.g = fill.b = 0;
	fill.opacity = 1;
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
		}
	}
}

vector<point> polyline::getVers() {
	return this->Vers;
}

void polyline::setVers(vector<point> Vers) {
	this->Vers = Vers;
}