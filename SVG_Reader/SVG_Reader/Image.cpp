#include "Lib.h"

void image::parseImage(parser parse) {
	parse.parseItem(figures, fileName);
	//parse.parseItem(figures, groupArr, fileName);
}

void image::renderImage(renderer render) {
	//render.renderItem(figures, groupArr, antialiasingLevel, imageName, width, height);
}

image::image(string fileInput) {
	this->fileName = fileInput;
	this->figures = {};
	this->width = 0;
	this->height = 0;
	this->antialiasingLevel = 8;
	this->imageName = "Image";
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

vector<figure*> image::getFigures() {
	return this->figures;
}

image::~image() {
	for (auto x : figures) {
		delete x;
		x = NULL;
	}
	deleteGroupArr(groupArr);
}
void image::deleteGroupArr(group_array& groupArr) {
	if (groupArr.arr.empty()) {
		return;
	}
	for (int i = 0; i < groupArr.arr.size(); i++) {
		if (groupArr.arr[i].groupArray.arr.empty()) {
			for (auto x : groupArr.arr[i].figureArray) {
				delete x;
				x = NULL;
			}
			return;
		}
		else {
			deleteGroupArr(groupArr.arr[i].groupArray);
		}
	}
}