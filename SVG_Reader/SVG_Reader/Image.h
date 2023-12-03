#ifndef _IMAGE_H_
#define _IMAGE_H_

class image {
private:
	//Image property
	string fileName, imageName;
	int width, height;
	float antialiasingLevel;

	//Figures Property
	vector<figure*> figures;
	group groupTemp; //Store all group in an svg file
	group_array groupArr;
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
	void renderImage(renderer);

	void deleteGroupArr(group_array&);

	~image();
};

#endif