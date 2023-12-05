#ifndef _PARSER_H_
#define _PARSER_H_

class parser {
private:
	unordered_map<string, color> colorMap;
	color processColor(string, string);
	void loadColorMap();
	void processProperty(string, string, string, figure*&);
	
	group generateGroup(vector<string>&, int);

	void parseGroupStr(string&);
public:
	void parseItem(vector<figure*>&, group_array& ,string);
};

#endif