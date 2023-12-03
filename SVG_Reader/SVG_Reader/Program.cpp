#include "Lib.h"

string program::name = "";
program* program::pg = NULL;

program::program() {
	currentFunc = run;
}

program* program::getObj(void(*pFunc)()) {
	if (pg == NULL)
		pg = new program();
	if (pFunc != NULL)
		pg->currentFunc = pFunc;
	return pg;
}

void program::run() {
	name = "sample.svg";
	image img(name);
	parser parseTool;
	renderer renderTool;
	img.parseImage(parseTool);
	//img.renderImage(renderTool);
}

void program::execute() {
	if (currentFunc != NULL)
		currentFunc();
}