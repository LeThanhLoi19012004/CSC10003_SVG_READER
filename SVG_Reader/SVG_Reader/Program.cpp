#include "Lib.h"

string program::name = "";
program* program::pg = NULL;

program::program() {
	currentFunc = run;
}

program* program::getObj(void(*pFunc)()) {
	if (pg == NULL)
		pg = new Program();
	if (pFunc != NULL)
		pg->currentFunc = pFunc;
	return pg;
}

void program::run() {
	name = "sample.svg";
	image img(name);
	parser parseTool;
	//Renderer renderTool;
	img.parseImage(parseTool);
	//image.renderImage(renderTool);
}

void program::execute() {
	if (currentFunc != NULL)
		currentFunc();
}