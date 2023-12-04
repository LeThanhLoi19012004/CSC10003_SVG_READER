#ifndef _PATH_H_
#define _PATH_H_

class path : public figure {
private:
	vector<pair<char, vector<point>>> vct;
public:
	path();
	~path();

	vector<pair<char, vector<point>>> getProp();
	/*Update different polyline element*/
	void updateProperty();

	//void transformFigure();
};

#endif