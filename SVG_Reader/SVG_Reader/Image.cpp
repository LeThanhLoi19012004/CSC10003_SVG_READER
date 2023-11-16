#include "Lib.h"

void Image::parseImage(Parser parse) {
	parse.parseItem(figures, fileName);
}

void Image::renderImage(Renderer render) {
	render.renderItem(figures, antialiasingLevel, imageName, width, height);
}

Image::Image(string fileInput) {
	this->fileName = fileInput;
	this->figures = {};
	this->width = 0;
	this->height = 0;
	this->antialiasingLevel = 8;
	this->imageName = "Image";
}

int Image::getHeight() {
	return this->height;
}

int Image::getWidth() {
	return this->width;
}

void Image::setHeight(int height) {
	this->height = height;
}

void Image::setWidth(int width) {
	this->width = width;
}

float Image::getAntialiasingLevel() {
	return this->antialiasingLevel;
}

void Image::setAntialiasingLevel(float atlvl) {
	this->antialiasingLevel = atlvl;
}

vector<Figure*> Image::getFigures() {
	return this->figures;
}

Image::~Image() {}