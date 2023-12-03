#ifndef _TEXT_H_
#define _TEXT_H_

class text :public figure {
private:
	float fontSize;
	point textPos;
	string content;
public:
	text();
	~text();
	/*Update different element of shape*/
	void updateProperty();

	/*Setter and Getter*/
	point getTextPos();
	float getFontSize();
	string getContent();

	void setTextPos(float, float);
	void setFontSize(float);
	void setContent(string);

	void transformFigure();
};

#endif