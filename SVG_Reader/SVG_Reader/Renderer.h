#ifndef _RENDERER_H_
#define _RENDERER_H_

class renderer {
public:
	//void canvasControl(sf::RenderWindow&, sf::View&, const float, const float);
	void drawFigure(vector<figure*>, HDC);
	////void drawGroup(GroupArray, sf::RenderWindow&);
	void renderItem(vector<figure*>, float, string, float, float, HDC);

	///*Draw the figure functions*/
	void drawRectangle(rectangle*, HDC);
	//void drawEllipse(sf::RenderWindow&, Ellipse*);
	//void drawLine(sf::RenderWindow&, Line*);
	//void drawPolygon(sf::RenderWindow&, Polygon*);
	//void drawPolyline(sf::RenderWindow&, Polyline*);
	//void drawText(sf::RenderWindow&, Text*);
	//void drawPath(sf::RenderWindow&, Path*);

};

#endif
