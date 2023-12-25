#ifndef _PARSER_H_
#define _PARSER_H_
class parser {
private:
	unordered_map<string, color> colorMap;
	void processColor(string, string, color&);
	void loadColorMap();
	void processProperty(string, string, string, figure*&, unordered_map<string, vector<string>>);
	//void parseGroupStr(string&);
public:
	void parseItem(group* ,string, viewbox&);
};

#endif