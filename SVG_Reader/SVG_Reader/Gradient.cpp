#include "Lib.h"

vector<stop> gradient::getStopVct() {
	return this->stopVct;
}

void gradient::setStopVct(vector<stop> vct) {
	this->stopVct = vct;
}

int gradient::getGradId() {
	return this->gradId;
}

void gradient::setGradId(int gradId) {
	this->gradId = gradId;
}

void gradient::addStop(stop stp) {
	stopVct.push_back(stp);
}

gradient::gradient() {
	stopVct = {};
}

gradient::gradient(const gradient& grad) {
	for (int i = 0; i < stopVct.size(); i++) {
		stopVct[i] = grad.stopVct[i];
	}
}

gradient& gradient::operator = (const gradient& grad) {
	if (this != &grad) {
		for (int i = 0; i < stopVct.size(); i++) {
			stopVct[i] = grad.stopVct[i];
		}
	}
	return *this;
}

vector<pair<string, vector<float>>> gradient::getGradientTrans() {
	return this->gradientTrans;
}

void gradient::updateGradientTransform(string str) {
	string token = "";
	stringstream ss(str);

	while (getline(ss, token, ')')) {
		token += " )";
		while (token[0] == ' ' || token[0] == ',')
			token.erase(0, 1);
		
		stringstream sss(token);
		string name = "", property;
		getline(sss, name, '(');
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
		else if (name == "rotate") {
			p.first = name;
			string r = "";
			ssss >> r;
			ssss.ignore();
			p.second.push_back(stof(r));
		}
		else if (name == "scale") {
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
		gradientTrans.push_back(p);
	}
}

string gradient::getStrLine() {
	return this->strLine;
}

void gradient::setStrLine(string line) {
	this->strLine = line;
}

void gradient::updateElement() {
	return;
}

gradient::~gradient() {}

stop::stop() {
	offset = 0;
}

stop::stop(color clr, float off) :stopColor(clr), offset(off) {}
