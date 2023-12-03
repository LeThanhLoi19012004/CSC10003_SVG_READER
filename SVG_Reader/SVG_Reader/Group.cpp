#include "Lib.h"
group::group() {
	figureArray = {};
	groupArray = {};
	propLine = "";
}

group::group(const group& grp) {
	this->figureArray = grp.figureArray;
	this->groupArray = grp.groupArray;
	this->propLine = grp.propLine;
}