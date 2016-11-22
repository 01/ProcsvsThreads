#Variable definition
CC  = gcc 
CCFLAGS = -Wall 

#rules definition
all : compressT

compressT : main.c compressRT.h compressT_LOLS.c RLEcompress.c
	$(CC) $(CCFLAGS) -pthread -o test main.c compressT_LOLS.c RLEcompress.c 

#This rule cleans up executable file


clean: 
	rm -f main