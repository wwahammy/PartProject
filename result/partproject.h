#pragma once 
#include "stdlib.h"
#include "stdio.h"
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#define IDFILE "___this_is_partproject"

int n, k, m;
short * parts =  0;

int __findInDir(char * dir)
{
	DIR * testDir = opendir(dir);
	while(testDir)
	{
		struct dirent * dp; 
		if ((dp = readdir(testDir)) != 0)
		{
			if (strcmp(dp->d_name, IDFILE) == 0)
			{
				closedir(testDir);
				return 1;
			}
		}
		else
		{
			closedir(testDir);
			return 0;
		}
	}
	
	
}

int partopen(char * n_arg, char * m_arg, char * k_arg)
{
	FILE * file;
	DIR * mntDir = opendir("/media");
	char filename[PATH_MAX];
	char rootDir[PATH_MAX];
	

	while (mntDir)
	{
		struct dirent * dp;
		if ((dp = readdir(mntDir)) != 0)
		{
			if (strcmp(dp->d_name, "..") != 0 && strcmp(dp->d_name, ".") != 0)
			{
				char dpName[PATH_MAX];
				sprintf(dpName,"/media/%s", dp->d_name);
				

				struct stat fileStat;
				if(!stat(dpName, &fileStat))
				{
					if(S_ISDIR(fileStat.st_mode))
					{
						
						//we have a dir
						if (__findInDir(dpName) == 1)
						{
							sprintf(rootDir, "%s", dpName);
							closedir(mntDir);
							break;
						}
					}
				}
				else
				{
					
					printf("we couldn't read a dir entry");
					return -1;
				}

			}
			
			
		}
		else
		{
			closedir(mntDir);
		}
		
		
	}
	//printf("rootdir == %s\n", rootDir);
	if (rootDir[0] != '/')
	{
		printf("We probably never found a root directory for the data. Is the hard drive connected and mounted?\n");
		return -1;
	}
	
	//create filename
	if (sprintf(filename, "%s/n%s/k%s/m%s/n%s_k%s_m%s", rootDir, n_arg, k_arg, m_arg, n_arg, k_arg, m_arg) < 0)
	{
		printf("Filename couldn't be created. Odd");
		return -1;
	}
	
	
	int * stuff;
	int ret;

	file = fopen(filename, "rb");
	if (file == 0)
	{
		printf("The file could not be opened. Did you provide the correct file path and name?\n");
		return -1;
	}

	stuff = (int *) malloc(sizeof(int)*3);
	ret = fread(stuff, 4, 3, file);
	if (ret == 0)
	{
		fclose(file);
		free(stuff);
		printf("the file could not be read in the first stage\n");
		return -1;
	}
	
	n = stuff[0];
	k = stuff[1];
	m = stuff[2];
	
	parts = (short *) malloc(sizeof(short)* n);
	
	ret = fread(parts, 2, n, file);
	if (ret == 0)
	{
		fclose(file);
		free(stuff);
		free(parts);
		printf("the file could not be read at the parts stage\n");
		return -1;
	}
	fclose(file);
	return 0;
};
