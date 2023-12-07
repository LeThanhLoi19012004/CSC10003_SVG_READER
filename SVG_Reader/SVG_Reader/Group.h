#ifndef _GROUP_H_
#define _GROUP_H_


class group:public figure {
	vector<figure*> figureArray;
	group* parent;
public:
	group();
	group(const group&);
	group& operator = (const group &);
	void setParent(group*);
	void setFigureArray(vector<figure*>);
	void addFigure(figure*);
	group* getParent();
	vector<figure*> getFigureArray();
	//group_array groupArray;
	//string propLine;
};
#endif