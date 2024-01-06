#ifndef _GROUP_H_
#define _GROUP_H_

class group : public figure {
private:
	vector<figure*> figureArray;
	group* parent;

public:
	group();
	group(const group&);
	group& operator = (const group &);

	void addFigure(figure*);

	void setParent(group*);
	void setFigureArray(vector<figure*>);

	group* getParent();
	vector<figure*> getFigureArray();
};

#endif