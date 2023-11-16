#include "Lib.h"

int main() {
	Program* program = Program::getObj(Program::run);
	program->execute();
	return 0;
}