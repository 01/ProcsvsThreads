#include "compressRT.h"


void compressT_LOLS(char * filename, int threadCount){

   if(threadCount < 1){

		printf("Error: Must have at least 1 thread.\n");
		exit(1);
   }

   FILE *fp;
   pthread_t * tid = (pthread_t *)malloc(sizeof(pthread_t)*threadCount);
   long length;
   fp = fopen(filename, "r");

   if(!fp){

	printf("Error: File not found.\n");
	exit(1);
   }
   else{
   		fseek(fp, 0L, SEEK_END);
   		length = ftell(fp)-1;
   		//printf("the file's length is %1dB\n", length);
   		rewind(fp);
   }
   if(threadCount>length){
   		printf("Error: Cannot have more threads than characters in file.\n");
   		exit(1);
   }
   int remainder = length % threadCount;
   int threadLength = (length - remainder) / threadCount;

   int i;
   int offset=0;
workInfo * work;
   for(i=0; i<threadCount; i++){
   		work= malloc(sizeof(workInfo));
   		work->filename = filename;
   		work->partID = i;
   		work->numPart = threadCount;

   		if(i==0){
   			work->length = threadLength + remainder;
   			work->offset=offset;
   			offset += work->length;
   		}
   		else {
   			work->length = threadLength;
   			work->offset = offset;
   			offset+=work->length; 
   		}
   		// printf("Offset: %d\n", work->offset);
   		pthread_create(&tid[i], NULL, (void *)&RLEcompress, (void *)work);
   }
   for(i=0; i<threadCount; i++){
   		pthread_join(tid[i], NULL);
   }

	free(tid);
	fclose(fp);
	return;
}
