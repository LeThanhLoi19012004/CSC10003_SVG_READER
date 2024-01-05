#ifndef _IMAGE_H_
#define _IMAGE_H_

class image {
private:
	//Image property
	string fileName; 
	group* root;

	/*
	string imageName;
	int width, height;
	float antialiasingLevel;*/

public:
	image(string);
	void parseImage(parser);
	void renderImage(renderer, Graphics&);
	~image();
	/*int getWidth();
	int getHeight();
	float getAntialiasingLevel();

	void setWidth(int);
	void setHeight(int);
	void setAntialiasingLevel(float);*/



	
};


#endif