#ifndef _POLYLINE_H_
#define _POLYLINE_H_

class polyline : public figure {
private:
	vector<point> Vers;

public:
	polyline();
	~polyline();

	void updateProperty();

	vector<point> getVers();
	void setVers(vector<point>);
};

#endif