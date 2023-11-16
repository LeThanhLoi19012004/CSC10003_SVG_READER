#ifndef _POLYLINE_H_
#define _POLYLINE_H_

class Polyline :public Figure {
private:
	int nVer;
	Point* Vers;
public:
	Polyline();
	~Polyline();

	/*Update different polyline element*/
	void updateDiffElement();

	/*Draw polyline*/
	void Draw(sf::RenderWindow&);
};

#endif