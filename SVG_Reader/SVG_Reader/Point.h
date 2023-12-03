#ifndef _POINT_H_
#define _POINT_H

class POINT {
private:
	float x, y;
	bool intersect;
public:
	POINT();
	~POINT();

	/*Setter and Getter*/
	float getX();
	float getY();
	bool getIntersect();

	void setIntersect(bool);
	void setX(float);
	void setY(float);

	//Operator == 
	friend bool operator == (const POINT&, const POINT&);
};

#endif