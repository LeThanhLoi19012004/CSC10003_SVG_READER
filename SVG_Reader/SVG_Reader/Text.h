#ifndef _TEXT_H_
#define _TEXT_H_

class text :public figure {
private:
	float fontSize, italic, dx, dy;
	point textPos;
	string content, fontFamily, textAnchor;
	

public:
	text();
	~text();
	/*Update different element of shape*/
	void updateProperty();

	/*Setter and Getter*/
	point getTextPos();
	float getFontSize();
	string getContent();
	string getFontFamily();
	string getTextAnchor();
	bool getItalic();
	float getDx();
	float getDy();

	void setTextPos(float, float);
	void setFontSize(float);
	void setContent(string);
	void setFontFamily(string);
	void setTextAnchor(string);
	void setItalic(bool);
	void setDx(float);
	void setDy(float);

	void transformFigure();
};

#endif