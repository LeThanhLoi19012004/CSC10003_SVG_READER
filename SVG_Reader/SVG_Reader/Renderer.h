#ifndef _RENDERER_H_
#define _RENDERER_H_

class Renderer {
public:
	void canvasControl(sf::RenderWindow&, sf::View&, const float, const float);
	void drawFigure(vector<Figure*>, sf::RenderWindow&);
	//void drawGroup(GroupArray, sf::RenderWindow&);
	void renderItem(vector<Figure*>, float, string, float, float);

	/*Draw the figure functions*/
	void drawRectangle(sf::RenderWindow&,Rectangle*);
	void drawEllipse(sf::RenderWindow&, Ellipse*);
	void drawLine(sf::RenderWindow&, Line*);
	void drawPolygon(sf::RenderWindow&, Polygon*);
	void drawPolyline(sf::RenderWindow&, Polyline*);
	void drawText(sf::RenderWindow&, Text*);
	//void drawPath(sf::RenderWindow&, Path*);

};

#endif
