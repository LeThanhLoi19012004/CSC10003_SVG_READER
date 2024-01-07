#include "Lib.h"

void parser::loadColorMap() {
	ifstream color_file("Color.txt", ios::in);

	if (!color_file.is_open()) {
		cout << "Error Loading Color File\n";
		return;
	}

	string color_line = "";
	while (getline(color_file, color_line)) {
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
		if (clr.r > 255)
			clr.r = 255.0;
		if (clr.g > 255)
			clr.g = 255.0;
		if (clr.b > 255)
			clr.b = 255.0;
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
		for (int i = 0; i < strokecolor.size(); i++)
			if (isupper(strokecolor[i]))
				strokecolor[i] = tolower(strokecolor[i]);
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

		if (attribute == "style") {
			for (int i = 0; i < value.size(); i++) {
				if (value[i] == ':') {
					value.insert(value.begin() + i + 1, '"');
					i++;
				}
				else if (value[i] == ';') {
					value.insert(value.begin() + i, '"');
					i++;
				}
			}
			value.push_back('"');


			for (int i = 0; i < value.size(); i++) {
				if (value[i] == ':' || value[i] == ';') 
					value[i] = ' ';
			}
			stringstream valStream(value);
			string attr, subVal, subTemp;

			while (valStream >> attr) {
				getline(valStream, subTemp, '"');
				getline(valStream, subVal, '"');
				if (attr == "fill") {
					if (subVal.find("url") != string::npos) {
						stringstream sss(subVal);
						isGradient = true;
						getline(sss, subTemp, '#');
						getline(sss, subVal, ')');
						getline(sss, subTemp, '"');
						while (subVal != "" && (subVal[subVal.size() - 1] == ' ' || subVal[subVal.size() - 1] == '"')) {
							subVal.erase(value.size() - 1, 1);
						}
					}
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
		}

		if (attribute == "stroke-width")
			strokeWidth = value;
		if (attribute == "fill-opacity")
			fillOpa = value;
		if (attribute == "fill") {
			if (value.find("url") != string::npos) {
				stringstream sss(value);
				isGradient = true;
				getline(sss, temp, '#');
				getline(sss, value,')');
				getline(sss, temp, '"');
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
		if (idMap.find(fill) != idMap.end()) {
			idMap[fill]->setGradId(1);
			fig->convertGradient(idMap[fill]);
		}
		else {
			fill = temp;
			fill += " 2";
			if (idMap.find(fill) != idMap.end()) {
				idMap[fill]->setGradId(2);
				fig->convertGradient(idMap[fill]);
			}
		}
	}

	else {
		color clr = { 0, 0, 0, 1 };
		if (fill == "none" || fill == "transparent")
			processColor(fill, "0", clr);
		else processColor(fill, fillOpa, clr);
		fig->setColor(clr);
		stroke strk;
		strk.setStrokeWidth(stof(strokeWidth));
		color strokeColor = { 0, 0, 0, 1 };

		if (sStroke == "none" || sStroke == "transparent" || sStroke == "")
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
	}
}

void parser::parseItem(group* root, string fileName, viewbox& vb) { 
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

	bool openDef = false, openLinear = false, openRadial = false;
	bool closeLinear = false, closeRadial = false;
	string idStr = "";
	vector<string> gradVct;

	vb.setPortWidth(0); vb.setPortHeight(0);
	float viewX = 0, viewY = 0, viewWidth = 0, viewHeight = 0, portWidth = 0, portHeight = 0;
	string preservedForm = "", preservedMode = "";

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
					if (val.find("pt") != string::npos)
					{
						portWidth *= 96.f / 72.f;
					}
					else if (val.find("cm") != string::npos)
					{
						portWidth *= 96.f / 2.54f;
					}
					vb.setPortWidth(portWidth);
				}
				if (attribute == "height") {
					portHeight = stof(val);
					if (val.find("pt") != string::npos)
					{
						portHeight *= 96.f / 72.f;
					}
					else if (val.find("cm") != string::npos)
					{
						portHeight *= 96.f / 2.54f;
					}
					vb.setPortHeight(portHeight);
				}
			}
		}
		
		if (name == "<defs>") {
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
					gradVct.push_back(remainLine);
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
					gradVct.push_back(remainLine);
					if (remainLine.find("xlink:href") != string::npos) {
						closeRadial = true;
					}
				}
				else {
					gradVct.push_back(property);
				}
			}

			if (name.find("/linearGradient") != string::npos) {
				openLinear = false;
				lineargradient* linear = new lineargradient;
				
				linear->setStrLine(gradVct[0]);
				linear->updateElement();

				for (int i = 1; i < gradVct.size() - 1; i++) {
					stop stp;
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
					linear->addStop(stp);
				}
				idStr += " 1";
				if (idMap.find(idStr) == idMap.end()) {
					linear->setGradId(1);
					idMap[idStr] = linear;
				}
				idStr = "";
				gradVct.clear();
			}
			if (name.find("/radialGradient") != string::npos || closeRadial) {
				openRadial = false;
				
				radialgradient* radial = new radialgradient;
				radial->setStrLine(gradVct[0]);
				radial->updateElement();

				if (closeRadial) { // Have link
					stringstream stream(gradVct[0]);
					string temp = "", val = "", attr = "", strLink = "";
					while (stream >> attr) {
						getline(stream, temp, '"');
						getline(stream, val, '"');
						if (attr == "xlink:href") {
							val.erase(0, 1);
							strLink = val;
							strLink += " 1";
							if (idMap.find(strLink) != idMap.end()) {
								for (int i = 0; i < idMap[strLink]->getStopVct().size(); i++) {
									radial->addStop(idMap[strLink]->getStopVct()[i]);
								}
							}
						}
					}
				}



				for (int i = 1; i < gradVct.size() - 1; i++) {
					stop stp;
					stringstream sss(gradVct[i]);
					string temp = "", attribute = "", value = "", stopColorStr = "", stopOpaStr = "1";
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
					radial->addStop(stp);

				}
				idStr += " 2";
				if (idMap.find(idStr) == idMap.end()) {
					radial->setGradId(2);
					idMap[idStr] = radial;
				}
				idStr = "";
				gradVct.clear();
				closeRadial = false;
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

parser::~parser() {}