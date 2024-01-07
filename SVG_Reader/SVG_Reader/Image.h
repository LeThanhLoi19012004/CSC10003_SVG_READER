#ifndef _IMAGE_H_
#define _IMAGE_H_

class image {
private:
	string fileName;
	group* root;

public:
	image(string);
	void parseImage(parser, viewbox&);
	void renderImage(renderer, Graphics&);
	~image();
};

#endif