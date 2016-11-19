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
} workInfo;

void * RLEcompress(void * work);

compressT_LOLS(char * filename, int threadCount){

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
   length--;
   int remainder = length % threadCount;
   int threadLength = (length - remainder) / threadCount;

   int i;
   int offset=0;
   for(i=0; i<threadCount; i++){
   		workInfo * work= malloc(sizeof(workInfo));
   		work->filename = "./stuff.txt";
   		work->thread_id = i;

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
   		 
   		pthread_create(&tid[i], NULL, &RLEcompress, (void *)work);
   }
   for(i=0; i<threadCount; i++){
   		pthread_join(tid[i], NULL);
   }

}
void* RLEcompress(void * workInf){
	
	workInfo * work = workInf;
	int unencodedLength = work->length;
	printf("Unencoded Length: %d\n",unencodedLength);
	int threadID = work->thread_id;
	printf("Thread %d\n", threadID);
	FILE * fp =  fopen(work->filename, "r");
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
		
		if(!isalpha(current))continue;
printf("Current character %c Count:%d\n", current, count);
		if(count==0) {
			currentLetter = current;
			count++;
			continue;
		}
		
		
		if( current != currentLetter || (i==(unencodedLength-1))){
			printf("COunt: %d", count);
			currentEncodedLength = strlen(encoded);
			if(count>2){
				sprintf((encoded+strlen(encoded)), "%d", count+1);
				*(encoded + strlen(encoded))= currentLetter;
				*(encoded + strlen(encoded)+1)= '\0';
			}
			else if (count == 2){
				printf("Makes it here\n");
				*(encoded + currentEncodedLength+2)= '\0';
				*(encoded + currentEncodedLength)= currentLetter;
				*(encoded + currentEncodedLength+1)= currentLetter;
				
				printf("Encoded : %s\n", encoded);
			}
			else{
				*(encoded + strlen(encoded))= currentLetter;
				*(encoded + strlen(encoded)+1)= '\0';
			}
		count = 1;
		currentLetter= current;
		}
		else count++;
	}
	encoded = realloc(encoded, strlen(encoded)+1);
	printf("Encoded %s\n", encoded);
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
compressT_LOLS("./stuff.txt", 3);

  return 0;
}