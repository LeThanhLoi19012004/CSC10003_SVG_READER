#ifndef _FIGURE_H_
#define _FIGURE_H_

class figure {
protected:
	// Figure name, textname
	string fig, text_name, line_str;
	gradient* grad;
	vector<pair<string, vector<float>>> transVct;
	// Stroke and fillings
	stroke strk;
	color fill;

public:

	figure();
	virtual ~figure();
	virtual void updateProperty();
	//Update element of figure
	string getName();
	string getTextName();
	stroke getStroke();
	color getColor();
	vector<pair<string, vector<float>>> getTransVct();
	gradient* getGrad();

	void setGrad(gradient*);
	void setName(string);
	void setTextName(string);
	void setLine(string);
	void setStroke(stroke);
	void setColor(color);
	void updateTransformVct(string);
	virtual void transformFigure(); //Transform Figure;
};

#endif