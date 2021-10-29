#include "commands.h"
#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <sys/stat.h>
#include "asm.h"

enum FileStatus asm_(char* input_file)
{
	char* buffer = NULL;
	Input(input_file, &buffer);
	
	char* ptr1 = buffer;
	
	do
	{
		if (*ptr1 == ' ' || *ptr1 == '\n')
			*ptr1 = '\0';
		ptr1++;
	} while (*ptr1 != '\0');
	
	FILE* fin = fopen("asm.txt", "w");
	const char* ptr = buffer;
	
	do
	{
		if (strcmp(ptr, "push") == 0)
		{
			do
			{
				ptr++;
			}while(*ptr != '\0');
			ptr++;
			fprintf(fin, "1 %s\n", ptr);
			while (*ptr != '\0')
			{
				ptr++;
			}
			ptr++;
		}
		
		else if (strcmp(ptr, "pop") == 0)
		{
			do
			{
				ptr++;
			}while(*ptr != '\0');
			ptr++;
			
			fprintf(fin, "2 %s\n", ptr);
			while (*ptr != '\0');
			{
				ptr++;
			}
			ptr++;
		}
		else if (strcmp(ptr, "add") == 0)
		{
			do
			{
				ptr++;
			}while(*ptr != '\0');
			ptr++;
			
			fprintf(fin, "3\n");

		}  
		
	} while (*ptr != '\0');
	
	struct stat file_inf;
    stat("asm.txt", &file_inf);
    int file_size = file_inf.st_size;
    
    free(buffer);
    fclose(fin);
    
    return (file_size == 0) ? EMPTY_FILE : OK;
}


