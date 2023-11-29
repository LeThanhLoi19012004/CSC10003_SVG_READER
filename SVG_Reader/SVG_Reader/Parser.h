#ifndef _PARSER_H_
#define _PARSER_H_


class Parser {
private:
	unordered_map<string, Color> colorMap;
	Color processColor(string , string);
	void loadColorMap();
	void processProperty(string, string, string, Figure*&);
	//Group getGroup(ifstream&,string);
	//Group generateGroup(string&, int);

	//void parseGroup(Group&);
public:
	void parseItem(vector<Figure*>&, string);
};
#endif