#include "Lib.h"

void parser::loadColorMap() {
	ifstream color_file("Color.txt", ios::in);

	if (!color_file.is_open()) {
		cout << "Error Loading Color File\n";
		return;
	}

	string color_line = "";
	while (getline(color_file, color_line)) {
		//int pos = color_line.find("#");
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
		color color;
		color.r = stoi(hexa_code.substr(1, 2), NULL, 16);
		color.g = stoi(hexa_code.substr(3, 2), NULL, 16);
		color.b = stoi(hexa_code.substr(5, 2), NULL, 16);

		colorMap[color_name] = color;
	}
	colorMap["none"] = { -1, -1, -1, -1 };
}

group parser::getGroup(ifstream& fin, string property) {
	string strGroup = "", temp = "";
	strGroup += ("<g " + property + ">");

	stack<string> bracket;

	while (getline(fin, temp, '>')) {
		if (temp.find("</g>") != string::npos) {
			strGroup += temp + ">";
			if (!bracket.empty()) {
				bracket.pop();
			}
			if (bracket.empty()) {
				break;
			}
		}
		else if (temp.find("<g") != string::npos) {
			bracket.push(temp);
			strGroup += temp + ">";
		}
		else {
			strGroup += temp + ">";
		}
	}
	stringstream ss(strGroup);

	group group;
	int index = 1;
	string parentProp = "";
	getline(ss, parentProp, '>');
	group = generateGroup(strGroup, index, parentProp);
	int cnt = 1;

	return group;
}

group parser::generateGroup(string& strGroup, int index, string parentProp) {
	group group;
	if (strGroup.empty()) return group;

	for (int i = index; i < strGroup.size() - 1; i++) {
		if (strGroup[i] == '<' && strGroup[i + 1] == 'g') {
			parentProp.erase(0, 2);
			strGroup.insert(i + 2, parentProp);
			string temp = strGroup;

			temp.erase(0, i);
			stringstream sss(temp);
			getline(sss, parentProp, '>');

			group.groupArray.arr.push_back(generateGroup(strGroup, i + 1, parentProp));
		}
		else if (strGroup[i] == 'g' && strGroup[i - 1] == '/') {
			group.propLine = strGroup.substr(index - 1, i + 3 - index);
			stringstream ss(group.propLine);
			string line = "", sameProp = "";
			getline(ss, sameProp, '>');
			sameProp.erase(0, 2);

			factoryfigure factory;

			while (getline(ss, line, '>')) {
				string name = "", property = "", textContent = "";
				stringstream stream(line);
				stream >> name;
				getline(stream, property, '/');
				property = sameProp + " " + property; //Same prop go before property so that you can overwritten the color
				name.erase(0, 1);

				if (name == "text") {
					string temp = "";
					getline(ss, textContent, '<');
					getline(ss, temp, '>');
				}
				for (int i = 0; i < property.size(); i++) {
					if (property[i] == '/' || property[i] == '=') {
						property[i] = ' ';
					}
				}
				figure* fig = factory.getFigure(name);

				if (fig) {
					processProperty(name, property, textContent, fig);
					group.figureArray.push_back(fig);
				}
			}
			strGroup.erase(index - 1, i + 3 - index);
			return group;
		}
	}
}

color parser::processColor(string strokecolor, string strokeopa) {
	if (strokecolor.find("rgb") != string::npos) {
		color clr = { -1,-1,-1,-1 };
		clr.opacity = stof(strokeopa);

		for (int i = 0; i < strokecolor.size(); i++) {
			if (!isdigit(strokecolor[i]))	//If the character is not number then change to ' '
				strokecolor[i] = ' ';
		}

		stringstream ss(strokecolor);
		string r, g, b;
		ss >> r >> g >> b;
		clr.r = stof(r); clr.g = stof(g); clr.b = stof(b);
		ss.ignore();
		return clr;

	}
	else if (strokecolor[0] == '#') {
		color clr;
		clr.r = stoi(strokecolor.substr(1, 2), NULL, 16);
		clr.g = stoi(strokecolor.substr(3, 2), NULL, 16);
		clr.b = stoi(strokecolor.substr(5, 2), NULL, 16);
		clr.opacity = stof(strokeopa);
		return clr;
	}
	else {
		color clr = { -1,-1,-1,-1 };
		clr = colorMap[strokecolor];
		clr.opacity = stof(strokeopa);
		return clr;
	}
}

void parser::processProperty(string name, string property, string textName, figure*& fig) {
	fig->setName(name);
	fig->setTextName(textName);
	fig->setLine(property);

	stringstream ss(property);
	string attribute, value;
	string strokeWidth = "0", sStroke = "", strokeOpa = "-1", fill = "", fillOpa = "-1";
	string strTransform = "";
	string temp = "";
	while (ss >> attribute) {
		//fill-opacity "100"
		getline(ss, temp, '"');
		getline(ss, value, '"');
		//cout << attribute << " " << value << '\n';
		if (attribute == "stroke-width")
			strokeWidth = value;
		if (attribute == "fill-opacity")
			fillOpa = value;
		if (attribute == "fill")
			fill = value; //rgb(.g.g.g)
		if (attribute == "stroke")
			sStroke = value;
		if (attribute == "stroke-opacity")
			strokeOpa = value;
		if (attribute == "transform") {
			strTransform = value;
		}
	}

	color clr = { -1,-1,-1,-1 };
	clr = processColor(fill, fillOpa);
	fig->setColor(clr);
	stroke strk;
	strk.setStrokeWidth(stof(strokeWidth));
	color strokeColor = { -1,-1,-1,-1 };
	strokeColor = processColor(sStroke, strokeOpa);
	strk.setStrokeColor(strokeColor);
	fig->setStroke(strk);
	fig->setisRotate(false);

	stringstream transformStream(strTransform);
	string token = "";
	fig->updateProperty();
	if (!strTransform.empty()) {
		fig->updateTransformVct(strTransform);
		fig->transformFigure();
	}

}

void parser::parseItem(vector<figure*>& figures, string fileName) {
	ifstream fin(fileName, ios::in);
	if (!fin.is_open()) {
		cout << "Error Opening SVG File\n";
		return;
	}
	loadColorMap();
	string line = "";
	factoryfigure factory;
	int id = 1;
	while (getline(fin, line, '>')) {

		string name = "", property = "", textContent = "";
		stringstream stream(line);
		stream >> name;
		getline(stream, property, '/');
		name.erase(0, 1);

		if (name == "text") {
			string temp = "";
			getline(fin, textContent, '<');
			getline(fin, temp, '>');
		}
		for (int i = 0; i < property.size(); i++) {
			if (property[i] == '/' || property[i] == '=') {
				property[i] = ' ';
			}
		}
		figure* fig = factory.getFigure(name);

		if (fig) {
			processProperty(name, property, textContent, fig);
			figures.push_back(fig);
		}
	}
}