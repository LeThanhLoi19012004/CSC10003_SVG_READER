#ifndef _LINE_H_
#define _LINE_H_

class Line :public Figure {
private:
	Point p1, p2;
public:
	Line();
	~Line();
	void updateProperty();
	/*Setter and Getter*/
	Point getP1();
	Point getP2();

	void setP1(Point);
	void setP2(Point);
	
	void transformFigure();
};

#endif