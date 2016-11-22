#Variable definition
CC  = gcc 
CCFLAGS = -Wall 

#rules definition
all : compressT

compressT : main.c compressRT.h compressT_LOLS.c RLEcompress.c
	$(CC) $(CCFLAGS) -pthread -o test main.c compressT_LOLS.c RLEcompress.c

compressR_worker : compressRT.h compressR_worker_LOLS.c RLEcompress.c
	$(CC) $(CCFLAGS) -o compressR_worker_LOLS compressR_worker_LOLS.c RLEcompress.c

compressR : main.c compressRT.h compressR_LOLS.c RLEcompress.c
	$(CC) $(CCFLAGS) -o test main.c compressR_LOLS.c RLEcompress.c

#This rule cleans up executable file


clean: 
	rm -f main
