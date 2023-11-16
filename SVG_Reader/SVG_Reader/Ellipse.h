#ifndef _ELLIPSE_H_
#define _ELLIPSE_H_

class Ellipse :public Figure {
protected:
	float rx, ry;
	Point center;
public:
	Ellipse();
	~Ellipse();

	void updateDiffElement();

	// Setter 
	Point getCenter();
	float getRx();
	float getRy();

	// Getter
	void setCenter(float, float);
	void setRx(float);
	void setRy(float);

	// Draw function
	void Draw(sf::RenderWindow&);
};

#endif 