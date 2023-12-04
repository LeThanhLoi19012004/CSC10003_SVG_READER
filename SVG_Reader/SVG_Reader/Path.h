#ifndef _PATH_H_
#define _PATH_H_

class path : public figure {
private:
	vector<pair<char, vector<point>>> vct;
	string strokeLineJoin, strokeLineCap;
public:
	path();
	~path();

	vector<pair<char, vector<point>>> getProp();
	string getStrokeLineJoin();
	string getStrokeLineCap();

	void setStrokeLineJoin(string);
	void setStrokeLineCap(string);
	void setVct(vector<pair<char, vector<point>>>);
	/*Update different polyline element*/
	void updateProperty();

	//void transformFigure();
};

#endif