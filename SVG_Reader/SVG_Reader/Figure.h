#ifndef _FIGURE_H_
#define _FIGURE_H_

class Figure {
protected:
	// Figure name, textname
	string figure;
	string text_name;

	// Stroke and fillings
	Stroke stroke;
	Color fill;

	string line;  //contain data of a figure
	unordered_map<string, Color> map_color;

	// Functions to process parameter
	void loadColorMap();
	Color processColor(string, string);

public:
	Figure();

	//Update element of figure
	void update(string, string, string);
	void updateSameElement(string, string, string);
	virtual void updateDiffElement();

	string getName();
	void setName(string);

	virtual ~Figure();
	virtual void Draw(sf::RenderWindow&);
};

#endif