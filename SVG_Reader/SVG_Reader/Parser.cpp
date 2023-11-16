#include "Lib.h"

void Parser::parseItem(vector<Figure*>& figures, string fileName) {
	ifstream fin(fileName, ios::in);

	if (!fin.is_open()) {
		cout << "Error";
		return;
	}

	string line, data;
	bool open = true;
	vector<string> lines;

	while (getline(fin, line)) {
		if (line.find("<") != string::npos)
			open = true;

		if (open)
			data = data + line;

		if (line.find(">") != string::npos) {
			if (data.find("text") != string::npos) {
				// the currrent data flow is text property
				if (line.find("</text>") != string::npos) {
					lines.push_back(data);
					data = "";
					open = false;
				}
			}
			else {
				lines.push_back(data);
				data = "";
				open = false;
			}
		}
	}

	FactoryFigure factory;

	for (string line : lines) {
		string name = "", attributes = "", textName = "";
		ProcessProperty(name, attributes, textName, line);
		Figure* fig = factory.getFigure(name);

		if (fig != NULL) {
			fig->update(name, attributes, textName);
			figures.push_back(fig);
		}
	}

}

void Parser::ProcessRGB(string& line) {
	int i = 0, j = 0;

	for (i = 1; i < line.size() - 1; i++) {
		if (line[i] == 'g' && line[i - 1] == 'r' && line[i + 1] == 'b') {
			j = i; //Assign j to i
			while (line[j] != ')' && j < line.size()) {
				if (line[j] == ' ')  //if line[j] == ' '=> erase the gap
					line.erase(j, 1); //delete the element;
				j++;
			}
		}
	}
}

void Parser::ProcessProperty(string& name, string& attribute, string& text_name, string line) {
	/* Remove all the gap in rgb detect any gab*/
	ProcessRGB(line);

	/* Rremove all uncessary symbol*/
	string symbol = "<>/\"=";
	text_name = ProcessTextName(line);

	for (int i = 0; i < line.size(); i++) {
		if (symbol.find(line[i]) != string::npos)
			line[i] = ' ';
	}

	stringstream lineStream(line);
	lineStream >> name; //Taking the name property;
	getline(lineStream, attribute);
	lineStream.ignore();
}

string Parser::ProcessTextName(string line) {
	string temp = line;
	if (line.find("text") != string::npos) {
		int pos = temp.find(">");
		temp.erase(0, pos);
		pos = temp.find("<");

		int i = temp.size();
		while (i > -1 && temp[i] != '<')
			i--;

		temp = temp.substr(1, i - 1);
		return temp;
	}
	else return "";
}