#ifndef _POLYLINE_H_
#define _POLYLINE_H_

class polyline :public figure {
private:
	vector<point> Vers;
public:
	polyline();
	~polyline();

	/*Update different polyline element*/
	void updateProperty();
	vector<point> getVers();
	void setVers(vector<point>);

	void transformFigure();
};

#endif