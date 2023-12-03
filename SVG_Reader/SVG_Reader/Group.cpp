#include "Lib.h"



Group::Group() {
	figureArray = {};
	groupArray = {};
	propLine = "";
}


Group::Group(const Group& group) {
	this->figureArray = group.figureArray;
	this->groupArray = group.groupArray;
	this->propLine = group.propLine;
}