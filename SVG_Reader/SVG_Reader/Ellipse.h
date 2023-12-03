#ifndef _ELLIPSE_H_
#define _ELLIPSE_H_

class ELLIPSE :public Figure {
protected:
	float rx, ry;
	POINT center;
public:
	ELLIPSE();
	~ELLIPSE();

	void updateProperty();

	// Setter 
	POINT getCenter();
	float getRx();
	float getRy();

	// Getter
	void setCenter(float, float);
	void setRx(float);
	void setRy(float);

	void transformFigure();
};

#endif 