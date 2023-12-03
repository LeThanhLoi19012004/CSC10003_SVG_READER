#ifndef _GROUP_H_
#define _GROUP_H_

class Group;
class GroupArray;


class GroupArray {
public:
	vector<Group> arr;
};
class Group {
public:
	Group();
	Group(const Group&);
	vector<Figure*> figureArray;
	GroupArray groupArray;
	string propLine;
};
#endif