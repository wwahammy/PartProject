#pragma once 
#include "stdlib.h"
#include "stdio.h"

int n, k, m;
short * parts =  0;
int partopen(char * filename)
{
	FILE * file;
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
