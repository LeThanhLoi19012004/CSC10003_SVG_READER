#ifndef _POLYLINE_H_
#define _POLYLINE_H_

class polyline :public figure {
private:
	int nVer;
	point* Vers;
public:
	polyline();
	~polyline();

	/*Update different polyline element*/
	void updateProperty();
	point* getVers();
	int getNVer();

	void setVers(point*);
	void setNVer(int);

	void transformFigure();
};

#endif