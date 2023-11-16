#ifndef _LINE_H_
#define _LINE_H_

class Line :public Figure {
private:
	Point p1, p2;
public:
	Line();
	~Line();
	void updateDiffElement();
	/*Setter and Getter*/
	Point getP1();
	Point getP2();

	void setP1(Point);
	void setP2(Point);
	/*Draw function*/
	void Draw(sf::RenderWindow&);
};

#endif