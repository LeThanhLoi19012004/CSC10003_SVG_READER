#include "Lib.h"

text::text() :figure() {
	textPos.setX(0);
	textPos.setY(0);
	fontSize = 16;
	content = "";
	dx = dy = 0;
	fontStyle = "";
	fontFamily = "Times New Roman";
	textAnchor = "start";
}

text::~text() {
	fontSize = 0;
	textPos.setX(0);
	textPos.setY(0);
	content = "";
}

void text::updateProperty() {
	size_t pos = line_str.find(">");
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
		if (attribute == "text-anchor")
			this->textAnchor = val;
		if (attribute == "font-family") {
			if (val.find("Time") == string::npos)
			this->fontFamily = val;
		}
		if (attribute == "font-style")
			this->fontStyle = val;
		if (attribute == "dx")
			this->dx = stof(val);
		if (attribute == "dy")
			this->dy = stof(val);
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

void text::setFontFamily(string fontFamily) {
	this->fontFamily = fontFamily;
}

void text::setTextAnchor(string textAnchor) {
	this->textAnchor = textAnchor;
}

void text::setFontStyle(string fontStyle) {
	this->fontStyle = fontStyle;
}

void text::setDx(float dx) {
	this->dx = dx;
}

void text::setDy(float dy) {
	this->dy = dy;
}

string text::getFontFamily() {
	return this->fontFamily;
}

string text::getTextAnchor() {
	return this->textAnchor;
}

string text::getFontStyle() {
	return this->fontStyle;
}

float text::getDx() {
	return this->dx;
}

float text::getDy() {
	return this->dy;
}