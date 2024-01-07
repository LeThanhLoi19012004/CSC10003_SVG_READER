#ifndef _RENDERER_H_
#define _RENDERER_H_

class renderer {
public:	
	void renderFigure(Graphics&, group*);

	void drawRectangle(Graphics&, rectangle*);
	void drawEllipse(Graphics&, ellipse*);
	void drawLine(Graphics&, line*);
	void drawPolygon(Graphics&, polygon*);
	void drawPolyline(Graphics&, polyline*);
	void drawText(Graphics&, text*);
	void drawPath(Graphics&, path*);
};

#endif
