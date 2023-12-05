#include "Lib.h"

figure::figure() {}

void figure::updateProperty() {}

string figure::getName() {
	return this->fig;
}

void figure::setName(string s) {
	this->fig = s;
}
void figure::setStroke(stroke stroke) {
	this->strk = stroke;
}
void figure::setColor(color fill) {
	this->fill = fill;
}
figure:: ~figure() {}

void figure::setTextName(string textName) {
	this->text_name = textName;
}
void figure::setLine(string line) {
	this->line_str = line;
}

string figure::getTextName() {
	return this->text_name;
}
stroke figure::getStroke() {
	return this->strk;
}
color figure::getColor() {
	return this->fill;
}

void figure::updateTransformVct(string str) {
	string token = "";
	stringstream ss(str);

	while (getline(ss, token, ')')) {
		token += " )";
		while (token[0] == ' ' || token[0] == ',')
			token.erase(0, 1);
		stringstream sss(token);

		string name = "", property;
		getline(sss, name, '('); //name = {Translate, rotate, scale};
		getline(sss, property, ')');
		for (int i = 0; i < property.size(); i++) {
			if (property[i] == ',') {
				property[i] = ' ';
				break;
			}
		}
		pair<string, vector<float>> p;

		stringstream ssss(property);
		if (name == "translate") {
			p.first = name;
			string x = "", y = "";
			ssss >> x >> y;
			ssss.ignore();
			p.second.push_back(stof(x));
			p.second.push_back(stof(y));
		}
		if (name == "rotate") {
			p.first = name;
			string r = "";
			ssss >> r;
			ssss.ignore();
			p.second.push_back(stof(r));
		}
		if (name == "scale") {
			p.first = name;
			int cnt = 0;
			for (int i = 0; i < property.size() - 1; i++) {
				if (isdigit(property[i]) && property[i + 1] == ' ') {
					++cnt;
				}
			}
			if (cnt == 1) {
				string s = "";
				ssss >> s;
				ssss.ignore();
				p.second.push_back(stof(s));
			}
			else {
				string x = "", y = "";
				ssss >> x >> y;
				ssss.ignore();

				p.second.push_back(stof(x));
				p.second.push_back(stof(y));
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