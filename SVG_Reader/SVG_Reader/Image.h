#ifndef _IMAGE_H_
#define _IMAGE_H_

class Image {
private:
	//Image property
	string fileName, imageName;
	int width, height;
	float antialiasingLevel;

	//Figures Property
	vector<Figure*> figures;
	Group groupTemp; //Store all group in an svg file
	GroupArray groupArr;
public:
	Image(string);
	int getWidth();
	int getHeight();
	float getAntialiasingLevel();
	vector<Figure*> getFigures();

	void setWidth(int);
	void setHeight(int);
	void setAntialiasingLevel(float);

	void parseImage(Parser);
	void renderImage(Renderer);

	~Image();
};

#endif