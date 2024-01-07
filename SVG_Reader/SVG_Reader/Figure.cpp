#include "Lib.h"

figure::figure() {
	grad = NULL;
	text_name = "", line_str = "", fig = "";
}

void figure::updateProperty() {}

string figure::getName() {
	return this->fig;
}

gradient* figure::getGrad() {
	return this->grad;
}

void figure::setGrad(gradient* grad) {
	if (grad->getGradId() == 1)
		this->grad = new lineargradient;
	else if (grad->getGradId() == 2)
		this->grad = new radialgradient;
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

figure:: ~figure() {
	delete grad;
	grad = NULL;
}

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
		getline(sss, name, '(');						//name = {Translate, rotate, scale};
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
		else if (name == "matrix") {
			p.first = name;
			string x1 = "", y1 = "", x2 = "", y2 = "", x3 = "", y3 = "";
			ssss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
			ssss.ignore();
			p.second.push_back(stof(x1));
			p.second.push_back(stof(y1));
			p.second.push_back(stof(x2));
			p.second.push_back(stof(y2));
			p.second.push_back(stof(x3));
			p.second.push_back(stof(y3));
		}
		transVct.push_back(p);
	}
}
vector<pair<string, vector<float>>> figure::getTransVct() {
	return this->transVct;
}

void figure::convertGradient(gradient* grad) {
	if (grad->getGradId() == 1) {
		this->grad = new lineargradient;
	}
	else if (grad->getGradId() == 2) {
		this->grad = new radialgradient;
	}
	else this->grad = NULL;
	this->grad = grad;
}