#include "Lib.h"

figure::figure() {}

void figure::updateProperty() {}

string figure::getName() {
	return this->fig;
}

void figure::setName(string s) {
	this->fig = s;
}
void ::setStroke(stroke stroke) {
	this->stroke = stroke;
}
void figure::setColor(color fill) {
	this->fill = fill;
}
figure:: ~figure() {}

void figure::setTextName(string textName) {
	this->text_name = textName;
}
void figure::setLine(string line) {
	this->line = line;
}

string figure::getTextName() {
	return this->text_name;
}
stroke figure::getStroke() {
	return this->stroke;
}
color figure::getColor() {
	return this->fill;
}


bool figure::getisRotate() {
	return this->isRotate;
}
void figure::setisRotate(bool isRotate) {
	this->isRotate = isRotate;
}
void figure::updateTransformVct(string str) {
	string tempStr = "", token = "";
	stringstream ss(str);
	while (ss >> token) {
		tempStr = tempStr + token;
	}
	stringstream tmpStream(tempStr);
	string property = "", val = "";

	while (getline(tmpStream, property, '(')) {
		pair<string, vector<float>> p;
		p.first = property;
		getline(tmpStream, val, ')');
		stringstream sss(val);
		if (property == "translate") {
			string x = "", y = "";
			getline(sss, x, ',');
			getline(sss, y);
			p.second.push_back(stof(x));
			p.second.push_back(stof(y));
		}
		else if (property == "rotate") {
			string r = "";
			getline(sss, r);
			p.second.push_back(stof(r));
		}
		else if (property == "scale") {
			if (val.find(",") != string::npos) {
				string x = "", y = "";
				getline(sss, x, ',');
				getline(sss, y);
				p.second.push_back(stof(x));
				p.second.push_back(stof(y));
			}
			else {
				string s = "";
				getline(sss, s, ',');
				p.second.push_back(stof(s));
			}
		}
		transVct.push_back(p);
	}
}
vector<pair<string, vector<float>>> figure::getTransVct() {
	return this->transVct;
}

void figure::transformFigure() {

}