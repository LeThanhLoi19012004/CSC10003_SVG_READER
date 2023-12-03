#ifndef _GROUP_H_
#define _GROUP_H_

class group;
class group_array;


class group_array {
public:
	vector<group> arr;
};
class group {
public:
	group();
	group(const group&);
	vector<figure*> figureArray;
	group_array groupArray;
	string propLine;
};
#endif