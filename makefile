#Variable definition
CC  = gcc 
CCFLAGS = -Wall 

#rules definition

all : main worker

main : main.c compressRT.h compressR_LOLS.c compressT_LOLS.c RLEcompress.c
	$(CC) $(CCFLAGS) -pthread -o main main.c compressR_LOLS.c compressT_LOLS.c RLEcompress.c

worker : compressRT.h compressR_worker_LOLS.c RLEcompress.c
	$(CC) $(CCFLAGS) -o compressR_worker_LOLS compressR_worker_LOLS.c RLEcompress.c

#This rule cleans up executable file


clean: 
	rm -f main
