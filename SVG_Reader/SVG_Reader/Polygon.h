#ifndef _POLYGON_H_
#define _POLYGON_H_

class Polygon : public Figure {
private:
	int nVer;
	Point* Vers;
public:
	Polygon();
	~Polygon();

	void setVers(Point*);
	void setNVer(int);
	Point* getVers();
	int getNVer();

	void updateProperty();
	void transformFigure();
};

#endif