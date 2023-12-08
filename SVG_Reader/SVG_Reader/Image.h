#ifndef _IMAGE_H_
#define _IMAGE_H_

class image {
private:
	//Image property
	string fileName, imageName;
	int width, height;
	float antialiasingLevel;
	group* root;
public:
	image(string);
	int getWidth();
	int getHeight();
	float getAntialiasingLevel();
	vector<figure*> getFigures();

	void setWidth(int);
	void setHeight(int);
	void setAntialiasingLevel(float);

	void parseImage(parser);
	void renderImage(renderer, HDC);

	~image();
};

#endif