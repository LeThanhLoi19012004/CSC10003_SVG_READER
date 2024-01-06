#include "Lib.h"

figure* factoryfigure::getFigure(std::string name) {
    int num = figureId[name];
    switch (num) {
        case 1: return new rectangle();
        case 2: return new circle();
        case 3: return new ellipse();
        case 4: return new line();
        case 5: return new polyline();
        case 6: return new polygon();
        case 7: return new text();
        case 8: return new path();
        case 9: return new group();
        default: return NULL;
    }
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

unordered_map<std::string, int> factoryfigure::getFigureId() {
    return this->figureId;
}
