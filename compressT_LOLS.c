#include "compressRT.h"


void compressT_LOLS(char * filename, int threadCount){

   FILE *fp;
   pthread_t tid[threadCount];
   long length;
   fp = fopen(filename, "r");

   if(!fp) printf("File not found\n");
   else{
   		fseek(fp, 0L, SEEK_END);
   		length = ftell(fp)-1;
   		printf("the file's length is %1dB\n", length);
   		rewind(fp);
   }
   if(threadCount>length){
   		printf("Can not create more threads then there are characters in file");
   		exit(1);
   }
   int remainder = length % threadCount;
   int threadLength = (length - remainder) / threadCount;

   int i;
   int offset=0;
   for(i=0; i<threadCount; i++){
   		
   		workInfo * work= malloc(sizeof(workInfo));
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
   		pthread_create(&tid[i], NULL, &RLEcompress, (void *)work);
   }
   for(i=0; i<threadCount; i++){
   		pthread_join(tid[i], NULL);
   }

}
