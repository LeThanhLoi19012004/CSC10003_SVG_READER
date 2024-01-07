#ifndef _PATH_H_
#define _PATH_H_

class path : public figure {
private:
	vector<pair<char, vector<float>>> vct;
	string strokeLineJoin, strokeLineCap, fillRule;

public:
	path();
	~path();

	vector<pair<char, vector<float>>> getProp();
	string getStrokeLineJoin();
	string getStrokeLineCap();
	string getFillRule();

	void setStrokeLineJoin(string);
	void setStrokeLineCap(string);
	void setFillRule(string);
	void setVct(vector<pair<char, vector<float>>>);

	void updateProperty();
};

#endif