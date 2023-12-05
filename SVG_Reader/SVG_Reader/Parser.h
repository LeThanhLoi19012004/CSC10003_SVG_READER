#ifndef _PARSER_H_
#define _PARSER_H_

class parser {
private:
	unordered_map<string, color> colorMap;
	void processColor(string, string, color&);
	void loadColorMap();
	void processProperty(string, string, string, figure*&);
	
	group generateGroup(vector<string>&, int);

	void parseGroupStr(string&);
public:
	void parseItem(vector<figure*>&, group_array& ,string);
};

#endif