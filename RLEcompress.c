
#include "compressRT.h"

int numDigits(int threads){
	int n = threads;
	int count = 1;
	while(n!=0){
		n/=10;
		++count;
	}
	return count;
}

void RLEcompress(void * workInf){
		
	workInfo * work = workInf;

	int unencodedLength = work->length;
	int partID = work->partID;\
	//printf("Thread # %d\n", partID);

	FILE* fp = fopen(work->filename, "r");
	char* outputFile = malloc(strlen(work->filename) + numDigits(partID) + 15);
	strcpy(outputFile, "./Output/");
	strcpy((outputFile + 9), work->filename);
	*(outputFile+strlen(outputFile)-4)='_';

	if(work->numPart > 1){
		sprintf((outputFile+strlen(outputFile)), "_LOLS%d", partID);
	}
	else{
		//printf("Makes it here1\n");
		sprintf((outputFile+strlen(outputFile)), "_LOLS");
	}
	//printf("%s: Length %d \n", outputFile, strlen(outputFile));
	//printf("Filename: %s\n", outputFile);	
	FILE* output = fopen(outputFile, "w");
	if(!output){
		printf("Output file part%d cannot be created\n", partID);
		exit(1);
	}

	if(!fp){
		printf("File to be decoded not found\n");
		exit(1);
	}
	else{
   		fseek(fp, work->offset, SEEK_SET);
	}


	char letter;
	char current;

	int count = 0;
	
	int i;
	for(i=0; i<unencodedLength; i++){

		current = fgetc(fp);
		
		if(!isalpha(current) && i<unencodedLength-1){
			continue;
		}

		if(count == 0) {

			letter = current;
		}

		count++;

		if(current != letter && i == unencodedLength-1){

			count--;

			if(count > 2){
				
				fprintf(output, "%d", count);
				fprintf(output, "%c", letter);
				
			}
			else if(count == 2){

				fprintf(output, "%c%c", letter, letter);
			}
			else{
				fprintf(output, "%c", letter);
			}

			if(isalpha(current)){
				fprintf(output, "%c", current);
			}

			continue;
		}
		
		if(current != letter){

			count--;

			if(count > 2){
				
				fprintf(output, "%d", count);
				fprintf(output, "%c", letter);
				
			}
			else if(count == 2){

				fprintf(output, "%c%c", letter, letter);
			}
			else{
				if(isalpha(current)){
					fprintf(output, "%c", letter);
				}
			}

			count = 1;
			letter = current;
		}

		if(i == unencodedLength-1){

			if(count > 2){
				
				fprintf(output, "%d", count);
				fprintf(output, "%c", letter);
				
			}
			else if(count == 2){

				fprintf(output, "%c%c", letter, letter);
			}
			else{
				if(isalpha(current)){
					fprintf(output, "%c", letter);
				}
			}
		}

	}

	fclose(fp);
	fclose(output);
	free(outputFile);
	free(work);
	
	
}
