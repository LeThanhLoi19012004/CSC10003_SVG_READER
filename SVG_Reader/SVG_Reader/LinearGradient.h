#pragma once
class stop:public color {
private:
	color stopColor;
	float stopOpa, offset;

public:
	color getStopColor();
	float getStopOpa();
	float getOffSet();

	void setStopColor(color);
	void setStopOpa(float);
	void setOffSet(float);
};
class lineargradient:public color {
private:
	vector<stop> stopVct;
	float x1, y1, x2, y2;
public:
	vector<stop> getStopVct();
	float getX1();
	float getY1();
	float getX2();
	float getY2();

	void setX1(float);
	void setY1(float);
	void setX2(float);
	void setY2(float);
};