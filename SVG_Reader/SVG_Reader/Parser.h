#ifndef _PARSER_H_
#define _PARSER_H_

class parser {
private:
	unordered_map<string, color> colorMap;
	void processColor(string, string, color&);
	void loadColorMap();
	void processProperty(string, string, string, figure*&);
	//group getGroup(ifstream&,string);
	//group generateGroup(string&, int,string);

	//void parseGroup(Group&);
public:
	void parseItem(vector<figure*>&, string);
};

#endif