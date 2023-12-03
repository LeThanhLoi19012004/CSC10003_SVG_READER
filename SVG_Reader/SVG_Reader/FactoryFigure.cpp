#include "Lib.h"

Figure* FactoryFigure::getFigure(string name) {

	int num = figureId[name];
	switch (num) {
	case 1: {
		return new Rectangle();
		break;
	}
	case 2: {
		return new Circle();
		break;
	}
	case 3: {
		return new Ellipse();
		break;
	}
	case 4: {
		return new Line();
		break;
	}
	case 5: {
		return new Polyline();
		break;
	}
	case 6: {
		return new Polygon();
		break;
	}
	case 7: {
		return new Text();
		break;
	}
	case 8: {
		return new Path();
		break;
	}
	default: return NULL;
	}
	return NULL;
}
FactoryFigure::FactoryFigure() {
	figureId["rect"] = 1;
	figureId["circle"] = 2;
	figureId["ellipse"] = 3;
	figureId["line"] = 4;
	figureId["polyline"] = 5;
	figureId["polygon"] = 6;
	figureId["text"] = 7;
	figureId["path"] = 8;
}
unordered_map<string, int> FactoryFigure::getFigureId() {
	return this->figureId;
}