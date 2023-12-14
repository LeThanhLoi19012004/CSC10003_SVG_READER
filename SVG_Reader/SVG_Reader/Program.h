#ifndef _PROGRAM_H_
#define _PROGRAM_H_

class program {
private:
	program();
	static program* pg;
	void(*currentFunc)();
	static string name;
public:
	static program* getObj(void (*currentFunc)() = NULL);
	static void run();
	void execute();
};

#endif