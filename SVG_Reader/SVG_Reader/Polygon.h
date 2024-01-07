#ifndef _POLYGON_H_
#define _POLYGON_H_

class polygon : public figure {
private:
	vector<point> Vers;

public:
	polygon();
	~polygon();

	void setVers(vector<point>);
	vector<point> getVers();

	void updateProperty();
};

#endif