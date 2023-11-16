#include "Lib.h"

string Program::name = "";
Program* Program::program = NULL;

Program::Program() {
	currentFunc = run;
}

Program* Program::getObj(void(*pFunc)()) {
	if (program == NULL)
		program = new Program();
	if (pFunc != NULL)
		program->currentFunc = pFunc;
	return program;
}

void Program::run() {
	name = "Sample.svg";
	Image image(name);
	Parser parseTool;
	Renderer renderTool;
	image.parseImage(parseTool);
	image.renderImage(renderTool);
}

void Program::execute() {
	if (currentFunc != NULL)
		currentFunc();
}