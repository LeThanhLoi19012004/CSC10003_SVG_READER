#ifndef _PARSER_H_
#define _PARSER_H_

class parser {
private:
	unordered_map<string, color> colorMap;
	unordered_map<string, gradient*> idMap;

	void processColor(string, string, color&);
	void loadColorMap();
	void processProperty(string, string, string, figure*&);

public:
	~parser();
	void parseItem(group* ,string, viewbox&);
};

#endif