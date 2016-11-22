#include "compressRT.h"

compressR_LOLS(char* fileName, int numParts){

	FILE* fp;
	fp = fopen(fileName, "r");

	fseek(fp, 0, SEEK_END);
	int fileSize = ftell(fp)-1;
	rewind(fp);

	printf("File contains %d characters\n", fileSize);

	int remainder = fileSize % numParts;
	int partSize = (fileSize - remainder) / numParts;

	pid_t pids[numParts];
	
	int offset = 0;
	int i;
	for(i=0; i<numParts; i++){

		int length;
			
		if(i == 0){
			
			length = partSize + remainder;
			offset += 0;
			printf("line 33 length:%d offset:%d\n", length, offset);
		}
			
		else{
			
			length = partSize;
			offset += length;
			printf("line 40 length:%d offset:%d\n", length, offset);
		}

		pids[i] = fork();
		
		if(pids[i] < 0){
			
			printf("Fork error.\n");
			exit(1);
		}
		
		if(pids[i] == 0){

			char** args = malloc(sizeof(char*) *6);
			args[0] = "./2compressR_worker_LOLS";
			args[1] = fileName;
			args[2] = (char *)malloc(numDigits(i)+1);
			args[3] = (char *)malloc(numDigits(numParts)+1);
			args[4] = (char *)malloc(numDigits(length)+1);
			args[5] = (char *)malloc(numDigits(offset)+1);
			sprintf(args[2], "%d", i);
			sprintf(args[3], "%d", numParts);
			sprintf(args[4], "%d", length);
			sprintf(args[5], "%d", offset);
			
			printf("line 65 %s %s %s %s\n", args[2], args[3], args[4], args[5]);

			execvp(args[0], args);
			
			printf("exec failure\n");
			exit(0);
		}
	}
	
	int status;
	for(i=0; i < numParts; i++){
		
		wait(&status);
	}

}
