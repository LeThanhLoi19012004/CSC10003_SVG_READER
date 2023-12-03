#ifndef _PARSER_H_
#define _PARSER_H_


class Parser {
private:
	unordered_map<string, COLOR> colorMap;
	COLOR processColor(string, string);
	void loadColorMap();
	void processProperty(string, string, string, Figure*&);
	Group getGroup(ifstream&,string);
	Group generateGroup(string&, int,string);

	//void parseGroup(Group&);
public:
	void parseItem(vector<Figure*>&, string);
};
#endif