#ifndef _COLORPROPERTY_H_
#define _COLORPROPERTY_H_

class Color {
public:
	float r, g, b;
};

class ColorProperty {
private:
	Color stroke, fill;
	float fillOpa, strokeWidth, strokeOpa;
public:
	void setStroke(Color);
	void setFill(Color);
	void setFillOpa(float);
	void setStrokeWidth(float);
	void setStrokeOpa(float);
	
	Color getStroke();
	Color getFill();
	float getFillOpa();
	float getStrokeWidth();
	float getStrokeOpa();
};

#endif