#ifndef _ELLIPSE_H_
#define _ELLIPSE_H_

class Ellipse :public Figure {
protected:
	float rx, ry;
	Point center;
public:
	Ellipse();
	~Ellipse();

	void updateProperty();

	// Setter 
	Point getCenter();
	float getRx();
	float getRy();

	// Getter
	void setCenter(float, float);
	void setRx(float);
	void setRy(float);

	void transformFigure();
};

#endif 