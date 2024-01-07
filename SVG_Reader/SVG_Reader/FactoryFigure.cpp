#include "Lib.h"

figure* factoryfigure::getFigure(string name) {
	int num = figureId[name];
	switch (num) {
	case 1: {
		return new rectangle();
		break;
	}
	case 2: {
		return new circle();
		break;
	}
	case 3: {
		return new ellipse();
		break;
	}
	case 4: {
		return new line();
		break;
	}
	case 5: {
		return new polyline();
		break;
	}
	case 6: {
		return new polygon();
		break;
	}
	case 7: {
		return new text();
		break;
	}
	case 8: {
		return new path();
		break;
	}
	case 9: {
		return new group();
		break;
	}
	default: return NULL;
	}
	return NULL;
}

factoryfigure::factoryfigure() {
	figureId["rect"] = 1;
	figureId["circle"] = 2;
	figureId["ellipse"] = 3;
	figureId["line"] = 4;
	figureId["polyline"] = 5;
	figureId["polygon"] = 6;
	figureId["text"] = 7;
	figureId["path"] = 8;
	figureId["g"] = 9;
}

unordered_map<string, int> factoryfigure::getFigureId() {
	return this->figureId;
}