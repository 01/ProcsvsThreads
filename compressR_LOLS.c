#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


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

		pids[i] = fork();
		
		if(pids[i] < 0){
			
			printf("Fork error.\n");
			exit(1);
		}
		
		if(pids[i] == 0){
			
			int length;
			
			if(i == 0){
				
				length = partSize + remainder;
				offset += length;
			}
			
			else{
				
				length = partSize;
				offset += length;
			}
			
			
			char* args[6];
			args[0] = "./compressR_worker_LOLS";
			args[1] = fileName;
			sprintf(args[2], "%d", i);
			sprintf(args[3], "%d", numParts);
			sprintf(args[4], "%d", length);
			sprintf(args[5], "%d", offset);
			
			
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

int main(int argc, char** argv){

	compressR_LOLS("test.txt", 2);

	return 0;
}
