
#include "compressRT.h"

int numDigits(int threads){
	int n = threads;
	int count = 0;
	while(n!=0){
		n/=10;
		++count;
	}
	return count;
}

void RLEcompress(void * workInf){
		
	workInfo * work = workInf;

	int unencodedLength = work->length;
	int partID = work->partID;

	FILE* fp = fopen(work->filename, "r");
	char* outputFile = malloc(strlen(work->filename) + numDigits(partID) + 5);
	strcpy(outputFile, work->filename);
	*(outputFile+strlen(outputFile)-4)='_';

	if(work->numPart > 1){
		sprintf((outputFile+strlen(outputFile)), "_LOLS%d", partID);
	}
	else{
		sprintf((outputFile+strlen(outputFile)), "_LOLS");
	}

	FILE* output = fopen(outputFile, "w");
	if(!output){
		printf("File not found\n");
	}

	if(!fp){
		printf("File not found\n");
	}
	else{
   		fseek(fp, work->offset, SEEK_SET);
	}

	char* encoded = malloc(unencodedLength+1);
	*encoded = '\0';

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
				fprintf(output, "%c", letter);
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
				fprintf(output, "%c", letter);
			}
		}

	}

	fclose(fp);
	free(work);
	encoded = realloc(encoded, strlen(encoded)+1);
	
}
