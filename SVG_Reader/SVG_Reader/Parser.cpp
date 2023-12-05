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
	colorMap["none"] = { 0, 0, 0, 0 };
}

color parser::processColor(string strokecolor, string strokeopa) {
	if (strokecolor.find("rgb") != string::npos) {
		color clr = { 0, 0, 0, 1 };
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
		color clr = { 0, 0, 0, 1 };
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
	string strokeWidth = "0", sStroke = "", strokeOpa = "1", fill = "", fillOpa = "1";
	string strTransform = "";
	string temp = "";
	while (ss >> attribute) {
		getline(ss, temp, '"');
		getline(ss, value, '"');
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
			/*translate(100  100)rotate(20)    traslate(100    200)*/
			/*for (int k = 0; k < value.size()-1; k++) {
				if (value[k] == ')' && value[k + 1] != ' ') {
					value.insert(k+1," ");
					k++;
				}
			}*/
			
			strTransform += (" "+value + " ");
		}
	}

	color clr = { 0, 0, 0, 1 };
	clr = processColor(fill, fillOpa);
	fig->setColor(clr);
	stroke strk;
	strk.setStrokeWidth(stof(strokeWidth));
	color strokeColor = { 0, 0, 0, 1 };
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
group parser::generateGroup(vector<string>& vct, int index) {
	group grp;
	for (int i = index; i < vct.size(); i++) {
		if (vct[i] == "<g>") {
			grp.groupArray.arr.push_back(generateGroup(vct, i + 1));
			vct[i] = " ";
		}
		else if (vct[i] == "</g>") {
			for (int j = index - 1; j <= i; j++) {
				vct[j] = " ";
			}
			stringstream ss(grp.propLine);
			string line_str = "";
			factoryfigure factory;

			while (getline(ss, line_str, '>')) {
				string name = "", property = "", textContent = "";
				stringstream stream(line_str);
				stream >> name;
				std::getline(stream, property, '/');
				name.erase(0, 1); //Get Figure Name

				if (name == "text") {
					string temp = "";
					std::getline(ss, textContent, '<');
					std::getline(ss, temp, '>');
				}
				for (int i = 0; i < property.size(); i++) {
					if (property[i] == '/' || property[i] == '=') {
						property[i] = ' ';

					}
					if (property[i] == '\'') {
						property[i] = '"';
					}
				}
				figure* fig = factory.getFigure(name);
				if (fig) {
					processProperty(name, property, textContent, fig);
					grp.figureArray.push_back(fig);
				}
			}
			return grp;
		}
		else {
			grp.propLine += vct[i];
		}

	}
	return grp;
}
void parser::parseGroupStr(string& str) {

	stringstream ss(str);
	string str_line = "";
	stack<string> stackString;
	string newStr = "";
	vector<string> groupVct;
	while (std::getline(ss, str_line, '>')) {
		str_line += ">";
		while (str_line[0] != '<' && str_line.find("</text>") == string::npos) {
			str_line.erase(0, 1);
		}
		if (str_line.find("<text") != string::npos) {
			string temp, groupText = "";
			std::getline(ss, groupText, '<');
			std::getline(ss, temp, '>');
			str_line += groupText + "</text>";
		}

		if (str_line.find("<g") != string::npos) {
			groupVct.push_back("<g>");
			string data = str_line.erase(0, 2);
			data.erase(data.size() - 1, 1);
			if (stackString.empty()) stackString.push(data);
			else {
				data = stackString.top() + " " + data;
				stackString.push(data);
			}
		}
		else if (str_line.find("</g") != string::npos) {
			if (!stackString.empty())
				stackString.pop();
			groupVct.push_back("</g>");
		}
		else {
			int pos = 0;
			while (pos < str_line.size() && str_line[++pos] != ' ');
			str_line.insert(pos, stackString.top());
			groupVct.push_back(str_line);
		}
	}
	group grp;
	grp = generateGroup(groupVct, 0);
}
void parser::parseItem(vector<figure*>& figures, group_array& grpArr, string fileName) {
	ifstream fin(fileName, ios::in);
	if (!fin.is_open()) {
		cout << "Error Opening SVG File\n";
		return;
	}
	loadColorMap();
	string line_str = "", group_str = "";
	factoryfigure factory;

	//int id = 1;
	bool openGroup = false;
	stack<string> groupStack;
	vector<string> groupVct;

	while (getline(fin, line_str, '>')) {

		string name = "", property = "", textContent = "";
		stringstream stream(line_str);
		stream >> name;
		getline(stream, property, '/');
		name.erase(0, 1);

		if (name == "text" && !openGroup) {
			string temp = "";
			getline(fin, textContent, '<');
			getline(fin, temp, '>');
		}
		if (name == "g" && !openGroup) {
			openGroup = true;
			line_str += ">";
			while (line_str[0] == ' ') {
				line_str.erase(0, 1);
			}
			group_str += line_str;
			groupStack.push(line_str);
		}
		else if (openGroup) {
			line_str += ">";
			if (name == "text") {
				string temp = "", grpText = "";
				std::getline(fin, grpText, '<');
				std::getline(fin, temp, '>');
				line_str += grpText + "</text>";
			}
			while (line_str[0] == ' ') {
				line_str.erase(0, 1);
			}
			group_str += line_str;
			if (line_str.find("<g") != string::npos) {
				groupStack.push(line_str);
			}
			else if (line_str.find("</g>") != string::npos) {
				if (!groupStack.empty()) {
					groupStack.pop();
				}
				if (groupStack.empty()) {
					openGroup = false;
					groupVct.push_back(group_str);
					group_str = "";
				}
			}
		}
		for (int i = 0; i < property.size(); i++) {
			if (property[i] == '/' || property[i] == '=') {
				property[i] = ' ';
			}
			if (property[i] == '\'') {
				property[i] = '"';
			}
		}
		figure* fig = factory.getFigure(name);
		if (fig) {
			if (!openGroup) {
				processProperty(name, property, textContent, fig);
				figures.push_back(fig);
			}
		}
	}
	fin.close();
}