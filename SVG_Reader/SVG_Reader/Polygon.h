#ifndef _POLYGON_H_
#define _POLYGON_H_

class Polygon : public Figure {
private:
	int nVer;
	Point* Vers;
public:
	Polygon();
	~Polygon();
	void updateDiffElement();
	void Draw(sf::RenderWindow&);
};

#endif