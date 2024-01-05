#include "Lib.h"

void image::parseImage(parser parse) {
	root = new group();
	//viewbox vb;
	//parse.parseItem(root, fileName, vb);
	parse.parseItem(root, fileName);
}

void image::renderImage(renderer render, Graphics& graphics) {
	
	//Graphics graphics(hdc);

	//Render Items
	render.renderItem(root, graphics);
}

image::image(string fileInput) {
	this->fileName = fileInput;
	
	this->root = NULL;
}


image::~image() {

	delete root;
	root = NULL;
}

