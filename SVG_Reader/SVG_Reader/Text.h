#ifndef _TEXT_H_
#define _TEXT_H_

class text :public figure {
private:
	float fontSize, dx, dy;
	point textPos;
	string content, fontFamily, textAnchor, fontStyle;
	
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
	string getFontStyle();
	float getDx();
	float getDy();

	void setTextPos(float, float);
	void setFontSize(float);
	void setContent(string);
	void setFontFamily(string);
	void setTextAnchor(string);
	void setFontStyle(string);
	void setDx(float);
	void setDy(float);

	void transformFigure();
};

#endif