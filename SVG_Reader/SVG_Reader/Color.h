#ifndef _COLOR_H_
#define _COLOR_H_

class color {
private:

public:
	float r = 0, g = 0, b = 0, opacity = 1;
	color() {}
	color(float r, float g, float b, float o): r(r), g(g), b(b), opacity(o){}
};

class stroke {
private:
	color strokeColor;
	float strokeWidth;
public:
	stroke();
	~stroke();

	color getStrokeColor();
	float getStrokeWidth();

	void setStrokeColor(color);
	void setStrokeWidth(float);
};

#endif