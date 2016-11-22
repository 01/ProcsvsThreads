#include "compressRT.h"

void compressR_worker_LOLS(workInfo* work){
	
	RLEcompress(work);
}

int main(int argc, char** argv){

	workInfo* work = (workInfo*)malloc(sizeof(workInfo));
	work->filename = argv[1];
	work->partID = atoi(argv[2]);
	work->numPart = atoi(argv[3]);
	work->length = atoi(argv[4]);
	work->offset = atoi(argv[5]);
	
	compressR_worker_LOLS(work);
	
	return 0;
}
