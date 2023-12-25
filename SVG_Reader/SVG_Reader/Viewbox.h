#ifndef _VIEWBOX_H_
#define _VIEWBOX_H_

class viewbox {
private:
	float viewX, viewY, viewWidth, viewHeight;
	float portWidth, portHeight; //This is the viewPort

	string preservedForm, preservedMode;
public:
	float getViewX();
	float getViewY();
	float getViewWidth();
	float getViewHeight();
	float getPortWidth();
	float getPortHeight();
	string getPreservedForm();
	string getPreservedMode();	

	
	void setPreservedMode(string);
	void setPreservedForm(string);
	void setPortWidth(float);
	void setPortHeight(float);
	void setViewWidth(float);
	void setViewHeight(float);
	void setViewX(float);
	void setViewY(float);

};
#endif