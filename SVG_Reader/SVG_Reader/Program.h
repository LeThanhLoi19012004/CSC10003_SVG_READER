#ifndef _PROGRAM_H_
#define _PROGRAM_H_

class Program {
private:
	Program();
	static Program* program;
	void(*currentFunc)();
	static string name;
public:
	static Program* getObj(void (*currentFunc)() = NULL);
	static void run();
	void execute();
};

#endif