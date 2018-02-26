/*
 ============================================================================
 Name        : Test.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <limits.h>

/* Concatenate directory Path */
char *ConcatenateDirPath(char *foo, char *dPath)
{
    char *ptr = malloc(strlen(foo) + strlen(dPath) + 2);
    strcpy(ptr, foo);
    strcat(ptr, "/");
    strcat(ptr, dPath);
    return ptr;
}

/*function to get size of the file.*/
long int findSizeOfFile(const char *filename)
{
    struct stat st;

    if(stat(filename, &st)==0)
        return (st.st_size);
    else
        return -1;
}

/* Get the Directories and Files*/
void Directories(char *path)
{
	long int totalSize = 0;
	long int size = 0;
	struct dirent *ep;
	DIR *dp;

	if ((dp = opendir(path)) != NULL)
	{
		while ((ep = readdir(dp)) != NULL)
		{
			if (ep->d_type == DT_DIR && ep->d_name[0] != '.')
			{
				char *dirPath = ConcatenateDirPath(path, ep->d_name);
				size = findSizeOfFile(dirPath);

				if(size != -1)
				{
					printf("\n================================\n");
					printf("Name of Dir : %s\n",ep->d_name);
					printf("Size of Dir : %ld\n",size);
					printf("Path of Dir : %s\n",dirPath);
				}
				else
				{
					printf("There is some ERROR.\n");
				}

				Directories(dirPath);
	        }
			else
			{
				if(ep->d_name[0] != '.')
				{
					char *dirPath = ConcatenateDirPath(path, ep->d_name);
					size = findSizeOfFile(dirPath);

					if(size != -1)
					{
						printf("\nFile Name : %s\n", ep->d_name);
						printf("Size Of File : %ld\n",size);
					}
					else
					{
						printf("There is some ERROR.\n");
					}

				}
			}
		}
	//closedir(dp);
	}
}

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("Please provide enough argument");
		printf("./a.out Your_Directory_Path");
		return 0;
	}

	printf("Path : %s\n", argv[1]);

	Directories(argv[1]);

	return 0;
}
