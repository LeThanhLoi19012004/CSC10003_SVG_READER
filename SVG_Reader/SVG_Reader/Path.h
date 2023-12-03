#ifndef _PATH_H_
#define _PATH_H_

class Path : public Figure {
private:
	vector<pair<char, vector<Point>>> vct;
public:
	Path();
	~Path();

	vector<pair<char, vector<Point>>> getProp();
	/*Update different polyline element*/
	void updateProperty();

	//void transformFigure();
};

#endif