#ifndef _POLYLINE_H_
#define _POLYLINE_H_

class Polyline :public Figure {
private:
	int nVer;
	Point* Vers;
public:
	Polyline();
	~Polyline();

	/*Update different polyline element*/
	void updateProperty();
	Point* getVers();
	int getNVer();
	
	void setVers(Point*);
	void setNVer(int);

	void transformFigure();
};

#endif