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