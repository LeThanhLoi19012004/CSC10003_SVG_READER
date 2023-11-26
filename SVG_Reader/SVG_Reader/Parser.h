#ifndef _PARSER_H_
#define _PARSER_H_


class Parser {
private:
	unordered_map<string, Color> colorMap;
	void ProcessRGB(string&);
	Color processColor(string , string);
	void loadColorMap();
	void processProperty(string, string, string, Figure*&);
	Group getGroup(ifstream&,string);
	Group generateGroup(string&, int, string);


public:
	void parseItem(vector<Figure*>&,GroupArray&, string);
};
#endif