#ifndef _TEXT_H_
#define _TEXT_H_

class Text :public Figure {
private:
	float fontSize;
	Point textPos;
	string content;
public:
	Text();
	~Text();
	/*Update different element of shape*/
	void updateProperty();

	/*Setter and Getter*/
	Point getTextPos();
	float getFontSize();
	string getContent();

	void setTextPos(float, float);
	void setFontSize(float);
	void setContent(string);

	void transformFigure();
};

#endif