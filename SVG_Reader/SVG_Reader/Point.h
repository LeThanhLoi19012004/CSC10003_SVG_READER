#ifndef _POINT_H_
#define _POINT_H

class point {
private:
	float x, y;
	bool intersect;
public:
	point();
	~point();

	/*Setter and Getter*/
	float getX();
	float getY();
	bool getIntersect();

	void setIntersect(bool);
	void setX(float);
	void setY(float);

	//Operator == 
	friend bool operator == (const point&, const point&);
};

#endif