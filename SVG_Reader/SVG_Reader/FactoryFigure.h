#ifndef _FACTORYFIGURE_H_
#define _FACTORYFIGURE_H_

class FactoryFigure {
private:
	unordered_map<string, int> figureId;
public:
	FactoryFigure();
	Figure* getFigure(string name);
	unordered_map<string, int> getFigureId();
};

#endif