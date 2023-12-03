#ifndef _FIGURE_H_
#define _FIGURE_H_

class figure {
protected:
	// Figure name, textname
	string fig, text_name, line;

	vector<pair<string, vector<float>>> transVct;
	// Stroke and fillings
	stroke strk;
	color fill;
	bool isRotate = false;
public:

	figure();
	virtual ~figure();
	virtual void updateProperty();
	//Update element of figure
	string getName();
	string getTextName();
	stroke getStroke();
	color getColor();
	bool getisRotate();
	vector<pair<string, vector<float>>> getTransVct();

	void setName(string);
	void setTextName(string);
	void setLine(string);
	void setStroke(stroke);
	void setColor(color);
	void setisRotate(bool);

	void updateTransformVct(string);
	virtual void transformFigure(); //Transform Figure;
};

#endif