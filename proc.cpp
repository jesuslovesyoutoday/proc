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
	int args = 0;
	char* ptr = proc->code;
	char reg = '0';
	double el = 0;
	int ok = 0;
	do
	{
		int cmd = (int)(*ptr - '0'); 
		
		switch (cmd) {
		
//-------------------------------------------------------------------------------------------------------//
		
		case PUSH:
		
			do
			{
				ptr++;
			} while (*ptr != '\0');
			ptr++;
			
			ok = 0;
			args = sscanf(ptr, "[%cx+%lg]%n", &reg, &el, &ok);
			if (args == 2 && ok == 6)
			{
				el = proc->ds[int(proc->regs[int(reg - 'a')] + el)];
				stackPush(&(proc->stack), (void*)&el);
			}
			else
			{
				ok = 0;
				args = sscanf(ptr, "%cx+%lg%n", &reg, &el, &ok);
				if (args == 2 && ok == 4)
				{
					el += proc->regs[(int)(reg - 'a')];
					stackPush(&(proc->stack), (void*)&el);
				}
				else
				{
					ok = 0;
					args = sscanf(ptr, "[%cx]%n", &reg, &ok);
					if (args == 1 && ok == 4)
					{
						el = proc->ds[int(proc->regs[int(reg - 'a')])];
						stackPush(&(proc->stack), (void*)&el);
					}
					else
					{
						ok = 0;
						args = sscanf(ptr, "[%lg]%n", &el, &ok);
						if (args == 1 && ok == 3)
						{
							el = proc->ds[int(el)];
							stackPush(&(proc->stack), (void*)&el);
						}
						else
						{
							ok = 0;
							args =sscanf(ptr, "%lg%n", &el, &ok);
							if (args == 1 && ok == 1)
							{
								stackPush(&(proc->stack), (void*)&el);
							}
							else
							{
								ok = 0;
								args = sscanf(ptr, "%cx%n", &reg, &ok);
								if (args == 1 && ok == 2)
								{
									el = proc->regs[(int)(reg - 'a')];
									stackPush(&(proc->stack), (void*)&el);
								}
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
			
//-------------------------------------------------------------------------------------------------------//
			
		case POP:
			do
			{
				ptr++;
			} while (*ptr != '\0');
			ptr++;
			
			ok = 0;
			args = sscanf(ptr, "%cx%n", &reg, &ok);
			if (args == 1 && ok == 2)
			{
				proc->regs[int(reg - 'a')] = stackPop(&(proc->stack));
			}
			else
			{
				ok = 0;
				args = sscanf(ptr, "[%cx]%n", &reg, &ok);
				if (args == 1 && ok == 4)
				{
					proc->ds[int(proc->regs[int(reg - 'a')])] = stackPop(&(proc->stack));
				}
				else
				{
					ok = 0;
					args = sscanf(ptr, "[%lg]%n", &el, &ok);
					if (args == 1 && ok == 3)
					{
						proc->ds[int(el)] = stackPop(&(proc->stack));
					}
					else
					{
						ok = 0;
						args = sscanf(ptr, "[%cx+%lg]%n", &reg, &el, &ok);
						if (args == 2 && ok == 6)
						{
							proc->ds[int(proc->regs[int(reg - 'a')] + el)] = stackPop(&(proc->stack));
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

//---------------------------------------------------------------------------------------------------------//

		case ADD:
			el = stackPop(&(proc->stack)) + stackPop(&(proc->stack));
			stackPush(&(proc->stack), (void*)&el);
			ptr += 2;
			break;
	}
	} while(*(ptr) != '\0');
}
