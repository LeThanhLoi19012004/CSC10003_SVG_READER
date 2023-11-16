#include "Lib.h"

Figure::Figure() {
	line = figure = text_name = "";
	this->stroke;
	this->fill.r = this->fill.g = this->fill.b = -1;
	this->fill.opacity = -1;
	loadColorMap();
}

void Figure::loadColorMap() {
	ifstream color_file("Color.txt", ios::in);

	if (!color_file.is_open()) {
		cout << "Error Loading Color File\n";
		return;
	}

	string color_line = "";
	while (getline(color_file, color_line)) {
		int pos = color_line.find("#");
		stringstream ss(color_line);
		string token = "";
		vector<string> vct;

		while (ss >> token)
			vct.push_back(token);

		string color_name, hexa_code;
		int n = vct.size();

		for (int i = 0; i < n - 1; i++)
			color_name = color_name + vct[i];

		hexa_code = vct[n - 1];
		Color color;
		color.r = stoi(hexa_code.substr(1, 2), NULL, 16);
		color.g = stoi(hexa_code.substr(3, 2), NULL, 16);
		color.b = stoi(hexa_code.substr(5, 2), NULL, 16);

		map_color[color_name] = color;
	}
	map_color["none"] = { -1, -1, -1, -1 };
}

void Figure::update(string name, string attribute, string text_name) {
	updateSameElement(name, attribute, text_name);
	updateDiffElement();
}

void Figure::updateSameElement(string figure, string attribute, string text_name) {
	this->line = attribute;
	this->figure = figure;
	this->text_name = text_name;

	stringstream ss(line);
	string property, value;
	string fillcolor = "", fillopa = "-1";
	string strokecolor = "", strokeopa = "-1";

	while (ss >> property >> value) {
		if (property == "stroke-width")
			this->stroke.setStrokeWidth(stof(value));
		if (property == "fill-opacity")
			fillopa = value;
		if (property == "fill")
			fillcolor = value;
		if (property == "stroke")
			strokecolor = value;
		if (property == "stroke-opacity")
			strokeopa = value;
	}

	this->fill = processColor(fillcolor, fillopa);
	this->stroke.setStrokeColor(processColor(strokecolor, strokeopa));
}

void Figure::updateDiffElement() {}

Color Figure::processColor(string strokecolor, string strokeopa) {
	if (strokecolor.find("rgb") != string::npos) {
		Color color = { -1, -1, -1, -1 };
		color.opacity = stof(strokeopa);
		for (int i = 0; i < strokecolor.size(); i++) {
			if (!isdigit(strokecolor[i]))	//If the character is not number then change to ' '
				strokecolor[i] = ' ';
		}
		stringstream ss(strokecolor);
		string r, g, b;
		ss >> r >> g >> b;
		color.r = stof(r); color.g = stof(g); color.b = stof(b);
		ss.ignore();
		return color;
	}
	else {
		//If the color property is Color
		Color color = map_color[strokecolor];
		color.opacity = stof(strokeopa);
		return color;
	}
}

string Figure::getName() {
	return this->figure;
}

void Figure::setName(string s) {
	this->figure = s;
}

Figure:: ~Figure() {}

void Figure::Draw(sf::RenderWindow& window) {
	return;
}