#include "proc.h"
#include <cstdlib>
#include "input/input.h"
#include "commands.h"

void procCtor(struct Proc* proc)
{
	stackCtor(proc->stack, double);
	proc->code = NULL;
	proc->ip = 0;
	proc->ds = (double*)calloc(20, sizeof(double));
	for (int i = 0; i < 4; i++)
	{
		proc->regs[i] = 0;
	}
}

void procDtor(struct Proc* proc)
{
	stackDtor(&(proc->stack));
	free(proc->code);
	proc->ip = 0;
	free(proc->ds);
	for (int i = 0; i < 4; i++)
	{
		proc->regs[i] = 0;
	}
}

void procExec(struct Proc* proc, char* filename)
{
	Input(filename, &(proc->code));
	char* ptr1 = proc->code;
	do
	{
		if (*ptr1 == '\n' || *ptr1 == ' ')
			*ptr1 = '\0';
		ptr1++;
	} while (*ptr1 != '\0');
	char* ptr = proc->code;
	char reg = '0';
	int el = 0;
	do
	{
		int cmd = (int)(*ptr - '0'); 
		
		switch (cmd) {
		case PUSH:
		
			do
			{
				ptr++;
			} while (*ptr != '\0');
			ptr++;
			int args = sscanf(ptr, "[%cx+%lg]", &reg, &el);
			if (args == 2)
			{
				el = proc->ds[int(reg - 'a') + el];
				stackPush(&(proc->stack), (void*)&el);
			}
			else
			{
				args = sscanf(ptr, "%cx+%lg", &reg, &el);
				if (args == 2)
				{
					el += proc->regs[(int)(reg - 'a')];
					stackPush(&(proc->stack), (void*)&el);
				}
				else
				{
					args = sscanf(ptr, "[%cx]", &reg);
					if (args == 1)
					{
						el = proc->ds[int(reg - 'a')];
						stackPush(&(proc->stack), (void*)&el);
					}
					else
					{
						args = sscanf(ptr, "[%lg]", &el);
						if (args == 1)
						{
							el = proc->ds[el];
							stackPush(&(proc->stack), (void*)&el);
						}
						else
						{
							args =sscanf(ptr, "%lg", &el);
							if (args == 1)
							{
								stackPush(&(proc->stack), (void*)&el);
							}
							else
							{
								args = sscanf(ptr, "%cx", &reg);
								el = proc->regs[(int)(reg - 'a')];
								stackPush(&(proc->stack), (void*)&el);
							}
						}
					}
				}
				
			}
			do
			{
				ptr++;
			} while (*ptr != '\0');
			ptr++;
			break;
		}
	} while(*(ptr) != '\0');
}
