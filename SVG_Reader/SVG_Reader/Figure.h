#ifndef _FIGURE_H_
#define _FIGURE_H_

class Figure {
protected:
	// Figure name, textname
	string figure, text_name, line;

	vector<pair<string, vector<float>>> transVct;
	// Stroke and fillings
	Stroke stroke;
	Color fill;
	bool isRotate = false;
public:

	Figure();
	virtual ~Figure();
	virtual void updateProperty();
	//Update element of figure
	string getName();
	string getTextName();
	Stroke getStroke();
	Color getColor();
	bool getisRotate();
	vector<pair<string, vector<float>>> getTransVct();

	void setName(string);
	void setTextName(string);
	void setLine(string);
	void setStroke(Stroke);
	void setColor(Color);
	void setisRotate(bool);

	void updateTransformVct(string);
	virtual void transformFigure(); //Transform Figure;
};

#endif