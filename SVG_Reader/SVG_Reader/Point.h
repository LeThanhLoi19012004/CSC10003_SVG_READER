#ifndef _POINT_H_
#define _POINT_H

class Point {
private:
	float x, y;
	bool intersect;
public:
	Point();
	~Point();
	/*Setter and Getter*/
	float getX();
	float getY();
	bool getIntersect();

	void setIntersect(bool);
	void setX(float);
	void setY(float);

	//Operator == 
	friend bool operator == (const Point&, const Point&);
};

#endif