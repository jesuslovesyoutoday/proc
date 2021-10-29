#include <stdio.h>
#include "asm.h"
#include <cstdlib>

int main()
{
	char input_file[200] = "prog.txt";
    asm_(input_file);

    return 0;
}
