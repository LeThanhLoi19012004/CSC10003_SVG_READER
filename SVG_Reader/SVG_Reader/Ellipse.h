#ifndef _ELLIPSE_H_
#define _ELLIPSE_H_

class ellipse : public figure {
protected:
	float rx, ry;
	point center;

public:
	ellipse();
	~ellipse();

	void updateProperty();

	point getCenter();
	float getRx();
	float getRy();

	void setCenter(float, float);
	void setRx(float);
	void setRy(float);
};

#endif 