#ifndef _FACTORYFIGURE_H_
#define _FACTORYFIGURE_H_

class FactoryFigure {
private:
	unordered_map<string, int> figureId;
public:
	Figure* getFigure(string name);
};

#endif