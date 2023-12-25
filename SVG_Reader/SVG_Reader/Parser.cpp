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

void parser::processColor(string strokecolor, string strokeopa, color& clr) {
	if (strokecolor.find("rgb") != string::npos) {
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
	}
	else if (strokecolor[0] == '#') {
		if (strokecolor.size() == 4) {
			string tmp = "#";
			for (int i = 1; i < 4; i++)
				tmp = tmp + strokecolor[i] + strokecolor[i];
			strokecolor = tmp;
		}
		clr.r = stoi(strokecolor.substr(1, 2), NULL, 16);
		clr.g = stoi(strokecolor.substr(3, 2), NULL, 16);
		clr.b = stoi(strokecolor.substr(5, 2), NULL, 16);
		clr.opacity = stof(strokeopa);
	}
	else {
		clr = colorMap[strokecolor];
		clr.opacity = stof(strokeopa);
	}
}

void parser::processProperty(string name, string property, string textName, figure*& fig, unordered_map<string, vector<string>> linearMap) {
	fig->setName(name);
	fig->setTextName(textName);
	fig->setLine(property);

	stringstream ss(property);
	string attribute, value;
	string strokeWidth = "1", sStroke = "", strokeOpa = "1", fill = "", fillOpa = "1";
	string strTransform = "";
	string temp = "";
	bool isGradient = false;

	while (ss >> attribute) {
		getline(ss, temp, '"');
		getline(ss, value, '"');
		/*if (attribute == "style") {
			int pos = value.find(';');
			if (pos != -1) value[pos] = ' ';
	
			stringstream valStream(value);
			string attr, subVal;
			while (getline(valStream, attr,':')) {
				if (attr == "fill") {
					fill = subVal;
				}
				if (attr == "fill-opacity") {
					fillOpa = subVal;
				}
				if (attr == "stroke-width") {
					strokeWidth = subVal;
				}
				if (attr == "stroke-opacity") {
					strokeOpa = subVal;
				}
				if (attr == "stroke") {
					sStroke = value;
				}
			}
		}*/
		if (attribute == "stroke-width")
			strokeWidth = value;
		if (attribute == "fill-opacity")
			fillOpa = value;
		if (attribute == "fill") {
			if (value.find("url") != string::npos) {
				//If you can find keyword url in 
				isGradient = true;
				getline(ss, temp, '#');
				getline(ss, value, '"');
				getline(ss, temp, '"');
				fill = value;
			}
			else fill = value; //rgb(.g.g.g)
		}
		if (attribute == "stroke")
			sStroke = value;
		if (attribute == "stroke-opacity")
			strokeOpa = value;
		if (attribute == "transform")
			strTransform += (" " + value + " ");
	}

	if (isGradient) {

	}
	else {
		color clr = { 0, 0, 0, 1 };
		if (fill == "none")
			processColor(fill, "0", clr);
		else processColor(fill, fillOpa, clr);
		fig->setColor(clr);
		stroke strk;
		strk.setStrokeWidth(stof(strokeWidth));
		color strokeColor = { 0, 0, 0, 1 };

		if (sStroke == "none" || sStroke == "")
			processColor(sStroke, "0", strokeColor);
		else processColor(sStroke, strokeOpa, strokeColor);
		strk.setStrokeColor(strokeColor);
		fig->setStroke(strk);

		stringstream transformStream(strTransform);
		string token = "";
		fig->updateProperty();
		if (!strTransform.empty()) {
			fig->updateTransformVct(strTransform);
			fig->transformFigure();
		}
	}
}

void parser::parseItem(group* root, string fileName, viewbox& vb) { 
	ifstream fin(fileName, ios::in);
	if (!fin.is_open()) {
		cout << "Error Opening SVG File\n";
		return;
	}
	loadColorMap();
	string line_str = "", group_str = "";
	factoryfigure factory;

	bool openGroup = false;
	stack<string> groupStack;
	vector<string> groupVct;
	
	groupStack.push(" ");
	group* curGroup = root;
	vb.setPortWidth(0); vb.setPortHeight(0);
	/*ViewBox*/
	float viewX = 0, viewY = 0, viewWidth = 0, viewHeight = 0, portWidth =  0, portHeight = 0;
	string preservedForm = "", preservedMode = "";
	/*Linear Gradient*/
	bool openDef = false, openLinear = false, openRadial = false;
	string linearId;
	unordered_map<string, vector<string>> linearMap;
	/*======*/
	while (getline(fin, line_str, '>')) {
		line_str += ">";
		string name = "", property = "", textContent = "";
		stringstream stream(line_str);
		stream >> name;
		getline(stream, property, '>');
		
		for (int i = 0; i < property.size(); i++) {
			if (property[i] == '/' || property[i] == '=') {
				property[i] = ' ';
			}
			if (property[i] == '\'') {
				property[i] = '"';
			}
		}
		if (name == "<svg") {
			stringstream sss(property);
			string attribute, temp, val;

			while (sss >> attribute) {
				getline(sss, temp, '"');
				getline(sss, val, '"');
				if (attribute == "viewBox") {
					stringstream ssss(val);

					ssss >> viewX >> viewY >> viewWidth >> viewHeight;
					ssss.ignore();
					vb.setViewX(viewX);
					vb.setViewY(viewY);
					vb.setViewWidth(viewWidth);
					vb.setViewHeight(viewHeight);
				}
				if (attribute == "preserveAspectRatio") {
					stringstream ssss(val);
					ssss >> preservedForm >> preservedMode;
					ssss.ignore();
					vb.setPreservedForm(preservedForm);
					vb.setPreservedMode(preservedMode);
				}
				if (attribute == "width") {
					portWidth = stof(val);
					vb.setPortWidth(portWidth);
				}
				if (attribute == "height") {
					portHeight = stof(val);
					vb.setPortHeight(portHeight);
				}
			}
		}
		if (name == "<defs") {
			//In the linear gradient scope
			openDef = true;
		}
		if (openDef) {

			if (name == "<linearGradient") {
				openLinear = true;
			}
			else if (name == "<radialGradient") {
				openRadial = true;
			}
			if (openLinear) { //If the current position is in the linear scope
				//std::cout << "Linear Scope\n";
				if (property.find("id") != string::npos) {

					int pos = property.find("id") + string("id").size();
					property.erase(0, pos);
					stringstream sss(property);
					string temp = "";
					getline(sss, temp, '"');
					string id = "";
					getline(sss, id, '"');
					string remain = "";
					getline(sss, remain);
					linearId = id;
					//linearId = "url('#" + linearId + "')";
					linearMap[linearId].push_back(remain);
				}
				else {
					linearMap[linearId].push_back(property);
				}


			}
			if (openRadial) {
				//std::cout << "Radial Scope\n";
				//std::cout << name << "\t\t" << property << "\n";
			}
			if (name.find("/linearGradient") != string::npos) {
				openLinear = false;
			}
			if (name.find("/radialGradient") != string::npos) {
				openRadial = false;
			}
		}
		if (name.find("/def") != string::npos) {
			openDef = false;
		}
		if (name.find("<g") != string::npos) {
	
			property = " "+groupStack.top() + " " + property+" ";
			groupStack.push(property);
		
			group* newGroup = new group(); 
			newGroup->setName("g");
			newGroup->setParent(curGroup);
			curGroup->addFigure(newGroup);
			curGroup = newGroup;
		}
		else if (name.find("</g") != string::npos) {
			if (!groupStack.empty()) 
				groupStack.pop();
			curGroup = curGroup->getParent();
		}
		else {
			name.erase(0, 1);

			if (name == "text") {
				string temp = "";
				getline(fin, textContent, '<');
				getline(fin, temp, '>');
			}
			
			figure* fig = factory.getFigure(name);
			if (fig) {
				if (!groupStack.empty()) {
					property = " "+ groupStack.top() + " " + property + " ";
				}
				processProperty(name, property, textContent, fig, linearMap);
				curGroup->addFigure(fig);	
			}
		}
	}

	fin.close();
}