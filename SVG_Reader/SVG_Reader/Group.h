#ifndef _GROUP_H_
#define _GROUP_H_

class group :public figure {
private:
	vector<figure*> figureArray;
public:
	group();
	group(const group&);
	
	vector<figure*> getFigureArray();
	void setFigureArray(vector<figure*>);
};
#endif