#include "Lib.h"

text::text() :figure() {
	textPos.setX(0);
	textPos.setY(0);
	fontSize = 0;
	content = "";
}

text::~text() {
	fontSize = 0;
	textPos.setX(0);
	textPos.setY(0);
	content = "";
}

void text::updateProperty() {
	int pos = line_str.find(">");
	string temp = line_str.substr(0, pos);
	stringstream ss(temp);
	string attribute, val, a;

	while (ss >> attribute) {
		getline(ss, a, '"');
		getline(ss, val, '"');
		if (attribute == "x")
			this->textPos.setX(stof(val));
		if (attribute == "y")
			this->textPos.setY(stof(val));
		if (attribute == "font-size")
			this->fontSize = stof(val);
	}
	this->content = text_name;
}

point text::getTextPos() {
	return this->textPos;
}

float text::getFontSize() {
	return this->fontSize;
}

string text::getContent() {
	return this->content;
}

void text::setTextPos(float x, float y) {
	this->textPos.setX(x);
	this->textPos.setY(y);
}

void text::setFontSize(float fontSize) {
	this->fontSize = fontSize;
}

void text::setContent(string content) {
	this->content = content;
}

void text::transformFigure() {
	/*float curX = this->textPos.getX();
	float curY = this->textPos.getY();
	for (auto p : transVct) {
		if (p.first == "translate") {
			this->textPos.setX(curX + p.second[0]);
			this->textPos.setY(curY + p.second[1]);

			curX = this->textPos.getX();
			curY = this->textPos.getY();
		}
		if (p.first == "rotate") {
			this->isRotate = true;
		}
		if (p.first == "scale") {
			curX = this->textPos.getX();
			curY = this->textPos.getY();
			if (p.second.size() == 1) {
				float scl = p.second[0];
				this->textPos.setX(curX * scl);
				this->textPos.setY(curY * scl);

				this->fontSize *= scl;

			}
			else {
				float sclX = p.second[0];
				float sclY = p.second[1];

				this->textPos.setX(curX * sclX);
				this->textPos.setY(curY * sclY);
				this->fontSize *= sclX;


			}
		}
	}*/
}