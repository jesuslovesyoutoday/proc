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
	setbuf(fin, NULL);
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
			
			if ((strcmp(ptr, "push") && strcmp(ptr, "pop") && strcmp(ptr, "add") && strcmp(ptr, "sub")
				&& strcmp(ptr, "mul") && strcmp(ptr, "div") && strcmp(ptr, "out")))
			{
				fprintf(fin, "2 %s\n", ptr);
				while (*ptr != '\0');
				{
					ptr++;
				}
				ptr++;
			}
			else
			{
				fprintf(fin, "2\n");
			}
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
		else if (strcmp(ptr, "sub") == 0)
		{
			do
			{
				ptr++;
			}while(*ptr != '\0');
			ptr++;
			
			fprintf(fin, "4\n");
		}
		else if (strcmp(ptr, "mul") == 0)
		{
			do
			{
				ptr++;
			}while(*ptr != '\0');
			ptr++;
			
			fprintf(fin, "5\n");
		}
		else if (strcmp(ptr, "div") == 0)
		{
			do
			{
				ptr++;
			}while (*ptr != '\0');
			ptr++;
			
			fprintf(fin, "6\n");
		}
		else if (strcmp(ptr, "out") == 0)
		{
			do
			{
				ptr++;
			}while (*ptr != '\0');
			ptr++;
			
			fprintf(fin, "7\n");
		}
		
	} while (*ptr != '\0');
	
	struct stat file_inf;
    stat("asm.txt", &file_inf);
    int file_size = file_inf.st_size;
    
    free(buffer);
    fflush(fin);
    fclose(fin);
    
    return (file_size == 0) ? EMPTY_FILE : OK;
}


