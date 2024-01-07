#ifndef _FACTORYFIGURE_H_
#define _FACTORYFIGURE_H_

class factoryfigure {
private:
	unordered_map<string, int> figureId;

public:
	factoryfigure();
	figure* getFigure(string name);
	unordered_map<string, int> getFigureId();
};

#endif