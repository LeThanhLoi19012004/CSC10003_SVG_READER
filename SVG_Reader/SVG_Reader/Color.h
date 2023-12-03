#ifndef _COLOR_H_
#define _COLOR_H_

class COLOR {
private:
	
public:
	float r = -1, g = -1, b = -1;
	float opacity = -1;
};

class Stroke {
private:
	COLOR strokeColor;
	float strokeWidth;
public:
	Stroke();
	~Stroke();

	COLOR getStrokeColor();
	float getStrokeWidth();

	void setStrokeColor(COLOR);
	void setStrokeWidth(float);
};

#endif