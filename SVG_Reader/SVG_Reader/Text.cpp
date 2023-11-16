#include "Lib.h"

Text::Text() :Figure() {
	textPos.setX(0);
	textPos.setY(0);
	fontSize = 0;
	content = "";
}

Text::~Text() {
	fontSize = 0;
	textPos.setX(0);
	textPos.setY(0);
	content = "";
}

void Text::updateDiffElement() {
	int pos = line.find(">");
	string temp = line.substr(0, pos);
	stringstream ss(temp);
	string attribute, val;

	while (ss >> attribute >> val) {
		if (attribute == "x")
			this->textPos.setX(stof(val));
		if (attribute == "y")
			this->textPos.setY(stof(val));
		if (attribute == "font-size")
			this->fontSize = stof(val);
	}
	this->content = text_name;
}

Point Text::getTextPos() {
	return this->textPos;
}

float Text::getFontSize() {
	return this->fontSize;
}

string Text::getContent() {
	return this->content;
}

void Text::setTextPos(float x, float y) {
	this->textPos.setX(x);
	this->textPos.setY(y);
}

void Text::setFontSize(float fontSize) {
	this->fontSize = fontSize;
}

void Text::setContent(string content) {
	this->content = content;
}

void Text::Draw(sf::RenderWindow& window) {
	sf::Text text;
	sf::Font font;

	if (!font.loadFromFile("times new roman.ttf"))
		return;

	text.setFont(font);
	text.setString(content);
	text.setCharacterSize(fontSize);

	if (fill.r != -1)
		text.setFillColor(sf::Color(fill.r, fill.g, fill.b));
	else text.setFillColor(sf::Color::Transparent);

	text.setPosition(textPos.getX(), textPos.getY() - fontSize - 1.f);
	window.draw(text);
}