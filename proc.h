#ifndef PROC_H
#define PROC_H
#include "stack/stack.h"

struct Proc
{
	Stack stack;
	char* code;
	int ip;
	double* ds;
	double regs[4];
};

void procCtor(struct Proc* proc);
void procExec(struct Proc* proc, char* filename);
void procDtor(struct Proc* proc);

#endif //PROC_H
