#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


char * RLEcompress(char * unencoded);

char * RLEcompress(char * unencoded){
	int unencodedLength = strlen(unencoded);
	char * encoded = malloc(unencodedLength);
	*encoded = '\0';
	char * encodedPTR = encoded;
	int letterCount = 0;
	char * currentPTR;
	char currentLetter;
	int count =0;
	for(int i=0; i<unencodedLength; i++){
		if(!isalpha(*(unencoded+i))) continue;
		if(count==0) currentLetter = *(unencoded + i);
		
		if(*(unencoded+i) != currentLetter || (i==(unencodedLength-1))){
			if(count>2){
				sprintf((encoded+strlen(encoded)), "%d", count);
				*(encoded + strlen(encoded))= currentLetter;
				*(encoded + strlen(encoded)+1)= '\0';
			}
			else if (count == 2){
				*(encoded + strlen(encoded))= currentLetter;
				*(encoded + strlen(encoded)+1)= currentLetter;
				*(encoded + strlen(encoded)+2)= '\0';
			}
			else{
				*(encoded + strlen(encoded))= currentLetter;
				*(encoded + strlen(encoded)+1)= '\0';
			}
		count = 1;
		currentLetter= *(unencoded + i);
		}
		else count++;
	
	}
	encoded = realloc(encoded, strlen(encoded)+1);
	return encoded;
}

int main(int argc, char *argv[]) {
   
   char * test = "aaaabbbbcccaaaaaaakk    888888kk8kkdddd";
   char * encoded =RLEcompress(test);
   printf("Encoded String: %s\n", encoded);

   FILE *fp;
   long length;
   char * filename = "stuff.txt";
   fp = fopen(filename, "r");
   if(!fp) printf("File not found\n");
   else{
   		fseek(fp, 0L, SEEK_END);
   		length = ftell(fp);
   		printf("the file's length is %1dB\n", length);
   		fclose(fp);
   }


  return 0;
}