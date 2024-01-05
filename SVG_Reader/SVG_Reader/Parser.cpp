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

void parser::processProperty(string name, string property, string textName, figure*& fig) {
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
				isGradient = true;//url
				getline(ss, temp, '#');
				getline(ss, value,')');
				getline(ss, temp, '"');
				while (value != "" && (value[value.size() - 1] == ' ' || value[value.size() - 1] == '"')) {
					value.erase(value.size() - 1, 1);
				}
			}
			fill = value;
		}
		if (attribute == "stroke")
			sStroke = value;
		if (attribute == "stroke-opacity")
			strokeOpa = value;
		if (attribute == "transform")
			strTransform += (" " + value + " ");
	}

	if (isGradient) {
		
		string temp = fill;
		fill += " 1";
		idMap[fill]->setGradId(1);

		if (idMap.find(fill) == idMap.end()) {
			fill = temp;
			fill += " 2";
			idMap[fill]->setGradId(2);
		}
		fig->setGrad(idMap[fill]);
	}
	else {
		//rgb #fff
		color clr = { 0, 0, 0, 1 };
		if (fill == "none" || fill == "transparent")
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
	}
	stringstream transformStream(strTransform);
	string token = "";
	fig->updateProperty();
	if (!strTransform.empty()) {
		fig->updateTransformVct(strTransform);
		fig->transformFigure();
	}
}

void parser::parseItem(group* root, string fileName) {
	ifstream fin(fileName, ios::in);
	if (!fin.is_open()) {
		cout << "Error Opening SVG File\n";
		return;
	}
	loadColorMap();
	
	string line_str = "";
	factoryfigure factory;

	bool openGroup = false;
	stack<string> groupStack;
	vector<string> groupVct;
	
	groupStack.push(" ");
	group* curGroup = root;
	//vb.setPortWidth(0); vb.setPortHeight(0);
	/*ViewBox*/
	//float viewX = 0, viewY = 0, viewWidth = 0, viewHeight = 0, portWidth =  0, portHeight = 0;
	string preservedForm = "", preservedMode = "";
	/*Linear Gradient*/
	bool openDef = false, openLinear = false, openRadial = false;
	string idStr = "";
	
	vector<string> gradVct;
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
					//stringstream ssss(val);

					//ssss >> viewX >> viewY >> viewWidth >> viewHeight;
					//ssss.ignore();
					//vb.setViewX(viewX);
					//vb.setViewY(viewY);
					//vb.setViewWidth(viewWidth);
					//vb.setViewHeight(viewHeight);
				}
				/*if (attribute == "preserveAspectRatio") {
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
				}*/
			}
		}
		
		if (name == "<defs") {
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
				if (property.find("id") != string::npos) {

					stringstream sss(property);
					string temp = "",  remainLine = "";
					getline(sss, temp, '"');
					getline(sss, idStr, '"');
					getline(sss, remainLine);

					 
					idMap[idStr] = NULL;
					gradVct.push_back(remainLine); //x1 y1 x2 y2 
				}
				else {
					gradVct.push_back(property);
				}
			}
			if (openRadial) {
				if (property.find("id") != string::npos) {
					stringstream sss(property);
					string temp = "", remainLine = "";
					getline(sss, temp, '"');
					getline(sss, idStr, '"');
					getline(sss, remainLine);
					
					idMap[idStr] = NULL;
					gradVct.push_back(remainLine); //x1 y1 x2 y2 

				}
				else {
					gradVct.push_back(property); //x1 y1 x2 
				}
			}

			if (name.find("/linearGradient") != string::npos) {
				openLinear = false;
				lineargradient linear;
				if (!gradVct[0].empty()) {
					stringstream sss(gradVct[0]);
					string temp = "", attribute = "", value = "";
					point ptA, ptB;
					while (sss >> attribute) {
						getline(sss, temp, '"');
						getline(sss, value, '"');

						if (attribute == "x1") {
							ptA.setX(stof(value));
						}
						if (attribute == "y1") {
							ptA.setY(stof(value));
						}
						if (attribute == "x2") {
							ptB.setX(stof(value));
						}
						if (attribute == "y2") {
							ptB.setY(stof(value));
						}
					}
					linear.setA(ptA);
					linear.setB(ptB);
				}
				stop stp;
				for (int i = 1; i < gradVct.size(); i++) {
					stringstream sss(gradVct[i]);
					string temp = "", attribute = "", value = "",stopColorStr = "",stopOpaStr = "1";
					while (sss >> attribute) {
						getline(sss, temp, '"');
						getline(sss, value, '"');

						if (attribute == "stop-color") {
							stopColorStr = value;
						}
						if (attribute == "stop-opacity") {
							stopOpaStr = value;
						}
						if (attribute == "offset") {
							stp.offset = stof(value);
						}
					}
					color clr = { 0, 0, 0, 1 };
					if (stopColorStr == "none" || stopColorStr == "transparent")
						processColor(stopColorStr, "0", clr);
					else processColor(stopColorStr, stopOpaStr, clr);
					stp.stopColor = clr;
					linear.addStop(stp);
				}
				idStr += " 1";
				idMap[idStr] = &linear;
				idStr = "";
			}
			if (name.find("/radialGradient") != string::npos) {
				openRadial = false;
				idStr += " 2";
				idMap[idStr] = new radialgradient;
				idStr = "";
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
				processProperty(name, property, textContent, fig);
				curGroup->addFigure(fig);	
			}
		}
	}

	fin.close();
}

parser::~parser() {
	for (auto& x : this->idMap) {
		
		delete x.second;
		x.second = NULL;
		
	}
}