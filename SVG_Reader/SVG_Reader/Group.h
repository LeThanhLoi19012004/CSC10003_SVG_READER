#ifndef _GROUP_H_
#define _GROUP_H_

//class Group;
//class GroupArray;


//class GroupArray {
//public: 
//	vector<Group> arr;
//};
//class Group {
//public:
//	vector<Figure*> figureArray;
//	GroupArray groupArray;
//	string propLine;
//};


class Group {
public:
	vector<Figure*> figs;
	Color colorGroup;
	Stroke strokeGroup;
	vector<pair<string, vector<float>>> transform;
	vector <Group> groups;
};

#endif
