#include "Lib.h"

void image::parseImage(parser parse, viewbox& vb) {
	root = new group();
	parse.parseItem(root, fileName, vb);
}

void image::renderImage(renderer render, Graphics& graphics) {
	render.renderFigure(graphics, root);
}

image::image(string fileInput) {
	this->fileName = fileInput;	
	this->root = NULL;
}

image::~image() {
	delete root;
	root = NULL;
}
