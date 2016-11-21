#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


compressR_worker_LOLS(workInfo* work){
	
	RLEcompress(work);
}

int main(int argc, char** argv){
	
	workInfo* work = (workInfo*)malloc(sizeof(workInfo))
	work->filename = args[1];
	work->process_id = atoi(args[2]);
	work->numProcesses = atoi(args[3]);
	work->length = atoi(args[4]);
	work->offset = atoi(args[5]);
	
	compressR_worker_LOLS(work);
	
	free(work);
	
	return 0;
}