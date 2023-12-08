#include "Lib.h"
group::group() {
	figureArray = {};
}

group::group(const group& grp) {
	this->figureArray = grp.figureArray;
}

vector<figure*> group::getFigureArray() {
	return this->figureArray;
}

void group::setFigureArray(vector<figure*> f) {
	this->figureArray = f;
}