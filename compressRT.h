#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>

typedef struct{
	int partID;
	char * filename;
	int length;
	int offset; 
	int numPart;
} workInfo;

int numDigits(int part);

void * RLEcompress(void * workInf);

void compressT_LOLS(char * filename, int threadCount);

void compressR_LOLS(char * filename, int threadCount);
