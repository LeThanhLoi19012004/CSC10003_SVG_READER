#include "Lib.h"


void Parser::loadColorMap() {
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

		colorMap[color_name] = color;
	}
	colorMap["none"] = { -1, -1, -1, -1 };
}

Color Parser::processColor(string strokecolor, string strokeopa) {

	if (strokecolor.find("rgb") != string::npos) {
		Color color = { -1,-1,-1,-1 };
		
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
	else  {
		Color color = { -1,-1,-1,-1 };
		color = colorMap[strokecolor];
		color.opacity = stof(strokeopa);
		return color;
	}

}

void Parser::processProperty(string name, string property, string textName, Figure*& fig) {
	fig->setName(name);
	fig->setTextName(textName);
	fig->setLine(property);

	stringstream ss(property);
	string attribute, value;
	string strokeWidth = "0",sStroke = "", strokeOpa= "-1", fill = "", fillOpa="-1";
	string strTransform = "";
	string temp = "";
	while (ss >> attribute) {
		//fill-opacity "100"
		getline(ss, temp,'"');
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
	
	Color color = { -1,-1,-1,-1 };
	color = processColor(fill, fillOpa);
	fig->setColor(color);
	Stroke stroke;
	stroke.setStrokeWidth(stof(strokeWidth));
	Color strokeColor = { -1,-1,-1,-1 };
	strokeColor = processColor(sStroke, strokeOpa);
	stroke.setStrokeColor(strokeColor);
	fig->setStroke(stroke);
	fig->setisRotate(false);
	
	stringstream transformStream(strTransform);
	string token = "";
	fig->updateProperty();
	if (!strTransform.empty()) {
		fig->updateTransformVct(strTransform);
		fig->transformFigure();
	}


}

void Parser::parseItem(vector<Figure*>& figures, string fileName) {
	ifstream fin(fileName, ios::in);
	if (!fin.is_open()) {
		cout << "Error Opening SVG File\n";
		return;
	}
	loadColorMap();
	string line = "";
	FactoryFigure factory;
	int id = 1;
	while (getline(fin, line, '>')) {

		string name = "", property = "", textContent="";
		stringstream stream(line);
		stream >> name;
		getline(stream, property,'/');
		name.erase(0, 1);

		if (name == "text") {
			string temp = "";
			getline(fin, textContent, '<');
			getline(fin, temp, '>');
		}
		for (int i = 0; i < property.size(); i++) {
			if (property[i] =='/' || property[i] == '=') {
				property[i] = ' ';
			}
		}
		Figure* fig = factory.getFigure(name);
		 
		if (fig) {
			processProperty(name, property, textContent, fig);
			figures.push_back(fig);
		}
	}
}
