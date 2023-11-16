#ifndef _COLORPROPERTY_H_
#define _COLORPROPERTY_H_

class Color {
private:

public:
	float r = -1, g = -1, b = -1;
	float opacity = -1;
};

class Stroke {
private:
	Color strokeColor;
	float strokeWidth;
public:
	Stroke();
	~Stroke();

	Color getStrokeColor();
	float getStrokeWidth();

	void setStrokeColor(Color);
	void setStrokeWidth(float);
};

#endif