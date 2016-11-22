#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>


typedef struct{
	int thread_id;
	char * filename;
	int length;
	int offset; 
	int numThreads;
} workInfo;

int numDigits(int threads){
	int n = threads;
	int count = 0;
	while(n!=0){
		n/=10;
		++count;
	}
	return count;
}
void * RLEcompress(void * work);

void compressT_LOLS(char * filename, int threadCount){

   FILE *fp;
   pthread_t tid[threadCount];
   long length;
   fp = fopen(filename, "r");

   if(!fp) printf("File not found\n");
   else{
   		fseek(fp, 0L, SEEK_END);
   		length = ftell(fp);
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
   		work->thread_id = i;
   		work->numThreads = threadCount;

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
void* RLEcompress(void * workInf){
	
	workInfo * work = workInf;
	int unencodedLength = work->length;
	//printf("Unencoded Length: %d\n",unencodedLength);
	int threadID = work->thread_id;
	//printf("Thread %d\n", threadID);
	FILE * fp =  fopen(work->filename, "r");
	char * outputFile = malloc(strlen(work->filename) + numDigits(threadID)+1);
	strcpy(outputFile, work->filename);
	*(outputFile+strlen(outputFile)-4)='_';
	if(work->numThreads > 1)sprintf((outputFile+strlen(outputFile)), "_LOLS%d", threadID);
	else sprintf((outputFile+strlen(outputFile)), "_LOLS");

	FILE * output = fopen(outputFile, "w");
	if(!output) printf("File not found\n");

	long length;
	 if(!fp) printf("File not found\n");
   else{
   		fseek(fp, work->offset, SEEK_SET);
   }
	char * encoded = malloc(unencodedLength);
	*encoded = '\0';
	char currentLetter, current;
	int count =0;
	int currentEncodedLength = 0;
	for(int i=0; i<unencodedLength; i++){
		current = fgetc(fp);
		//printf("Letter : %c  Iteration: %d\n",current, i);
		//if(threadID==2) printf("Character %c Count: %d\n", current, count);
		if(!isalpha(current) && i<unencodedLength-1)continue;
		if(count==0) {
			currentLetter = current;
			count++;
			continue;
		}
		
		
		if( current != currentLetter || (i==(unencodedLength-1))){
			currentEncodedLength = strlen(encoded);
			if(count>2){
				//printf("Count: %d Letter: %c i: %d", count, currentLetter, i);
				//if(threadID==2) printf("Makes it here");
				//if(i==(unencodedLength-1)) count++;
				fprintf(output, "%d", count);
				fprintf(output, "%c", currentLetter);
				
			}
			else if (count == 2){
				fprintf(output, "%c%c", currentLetter, currentLetter);
				
				
			}
			else{
				fprintf(output, "%c", currentLetter);
			}
		count = 1;
		currentLetter= current;
		}
		else count++;
	}
	close(fp);
	free(work);
	encoded = realloc(encoded, strlen(encoded)+1);
	printf("Thread %d: Encoded %s\n", threadID, encoded);
}

int main(int argc, char *argv[]) {
   

	workInfo * work = malloc(sizeof(workInfo));
	FILE * fp;
	char * filename = "stuff.txt";
 	fp = fopen(filename, "r");
   if(!fp) printf("File not found\n");
   else{
   		fseek(fp, 0L, SEEK_END);
   		long length = ftell(fp);
   		printf("the file's length is %1dB\n", length);
   		rewind(fp);
   }
   rewind(fp);
  printf("Makes it here\n");
compressT_LOLS("./stuff.txt", 2);

  return 0;
}