#include <stdio.h>
#include "stack/stack.h"
#include "proc.h"

int main()
{
	struct Proc proc;
	procCtor(&proc);
	char filename[200] = "asm.txt";
	procExec(&proc, filename);
	procDtor(&proc);
}	
