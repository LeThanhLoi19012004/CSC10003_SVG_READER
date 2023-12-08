#ifndef _RENDERER_H_
#define _RENDERER_H_

class renderer {
public:
	//void canvasControl(sf::RenderWindow&, sf::View&, const float, const float);
	void renderItem(vector<figure*>, float, string, float, float, HDC);
	void drawFigure(Graphics&, vector<figure*>);

	///*Draw the figure functions*/
	void drawRectangle(Graphics&, rectangle*);
	void drawEllipse(Graphics&, ellipse*);
	void drawLine(Graphics&, line*);
	void drawPolygon(Graphics&, polygon*);
	void drawPolyline(Graphics&, polyline*);
	void drawText(Graphics&, text*);
	void drawPath(Graphics&, path*);
	void drawGroup(Graphics&, group*);
};

#endif
