#include "Lib.h"

Figure::Figure() {}

void Figure::updateProperty() {}

string Figure::getName() {
	return this->figure;
}

void Figure::setName(string s) {
	this->figure = s;
}
void Figure::setStroke(Stroke stroke) {
	this->stroke = stroke;
}
void Figure::setColor(Color fill) {
	this->fill = fill;
}
Figure:: ~Figure() {}

void Figure::setTextName(string textName) {
	this->text_name = textName;
}
void Figure::setLine(string line) {
	this->line = line;
}

string Figure::getTextName() {
	return this->text_name;
}
Stroke Figure::getStroke() {
	return this->stroke;
}
Color Figure::getColor() {
	return this->fill;
}


bool Figure::getisRotate() {
	return this->isRotate;
}
void Figure::setisRotate(bool isRotate) {
	this->isRotate = isRotate;
}
void Figure::updateTransformVct(string str) {
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
vector<pair<string, vector<float>>> Figure::getTransVct() {
	return this->transVct;
}

void Figure::transformFigure() {

}