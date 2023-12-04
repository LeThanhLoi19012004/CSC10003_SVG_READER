#ifndef _COLOR_H_
#define _COLOR_H_

class color {
private:
	
public:
	float r = 0, g = 0, b = 0;
	float opacity = 1;
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