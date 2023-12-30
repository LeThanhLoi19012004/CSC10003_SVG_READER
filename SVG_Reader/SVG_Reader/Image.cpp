#include "Lib.h"

void image::parseImage(parser parse) {
	root = new group();
	parse.parseItem(root, fileName);
}

void image::renderImage(renderer render, Graphics& graphics) {
	render.renderItem(root, antialiasingLevel, imageName, width, height, graphics);
}

image::image(string fileInput) {
	this->fileName = fileInput;
	this->width = 0;
	this->height = 0;
	this->antialiasingLevel = 8;
	this->imageName = "Image";
	this->root = NULL;
}

int image::getHeight() {
	return this->height;
}

int image::getWidth() {
	return this->width;
}

void image::setHeight(int height) {
	this->height = height;
}

void image::setWidth(int width) {
	this->width = width;
}

float image::getAntialiasingLevel() {
	return this->antialiasingLevel;
}

void image::setAntialiasingLevel(float atlvl) {
	this->antialiasingLevel = atlvl;
}

image::~image() {
	delete root;
	root = NULL;
}