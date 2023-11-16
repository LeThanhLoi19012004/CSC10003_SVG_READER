#ifndef _PARSER_H_
#define _PARSER_H_

class Parser {
private:
	void ProcessRGB(string&);
	void ProcessProperty(string&, string&, string&, string);
	string ProcessTextName(string);
public:
	void parseItem(vector<Figure*>&, string);
};

#endif