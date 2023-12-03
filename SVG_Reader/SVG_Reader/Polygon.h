#ifndef _POLYGON_H_
#define _POLYGON_H_

class polygon : public figure {
private:
	int nVer;
	point* Vers;
public:
	polygon();
	~polygon();

	void setVers(point*);
	void setNVer(int);
	point* getVers();
	int getNVer();

	void updateProperty();
	void transformFigure();
};

#endif