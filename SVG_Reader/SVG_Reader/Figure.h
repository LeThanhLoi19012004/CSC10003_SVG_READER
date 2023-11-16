#ifndef _FIGURE_H_
#define _FIGURE_H_

class Figure {
protected:
	string figure;
	string text_name;
	ColorProperty colorProp;
	
	//Update all of color property
	string line;  /*contain data of a figure*/
	unordered_map<string, Color> map_color;

	//Functions to process parameter
	void loadColorMap();
	Color processColor(string);
public:
	Figure();
	virtual ~Figure();

	/*Update element of figure*/
	void update(string, string ,string);
	void updateSameElement(string, string, string);
	virtual void updateDiffElement();

	/*Setter and Getter method*/
	string getName();
	void setName(string);

	//Draw
	virtual void Draw(sf::RenderWindow&);	
};

#endif