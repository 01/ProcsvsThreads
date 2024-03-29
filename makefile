
#Variable definition
CC  = gcc 
CCFLAGS = -Wall 

#rules definition

all : main worker

main : main.c compressRT.h compressR_LOLS.c compressT_LOLS.c RLEcompress.c
	$(CC) $(CCFLAGS) -pthread -o main main.c compressR_LOLS.c compressT_LOLS.c RLEcompress.c

compressGrind : compressGrind.c compressRT.h compressR_LOLS.c compressT_LOLS.c RLEcompress.c
	$(CC) $(CCFLAGS) -pthread -o compressGrind compressGrind.c compressR_LOLS.c compressT_LOLS.c RLEcompress.c

compressR: compressRT.h compressR_LOLS.c RLEcompress.c compressRT.h
	$(CC) $(CCFLAGS) -o compressR compressR_LOLS.c RLEcompress.c

compressT: compressRT.h compressT_LOLS.c RLEcompress.c compressRT.h
	$(CC) $(CCFLAGS) -o compressT compressT_LOLS.c RLEcompress.c

compressK: compressK_LOLS.c RLEcompress.c compressRT.h
	$(CC) $(CCFLAGS) -o compressK compressK_LOLS.c RLEcompress.c

worker : compressRT.h compressR_worker_LOLS.c RLEcompress.c
	$(CC) $(CCFLAGS) -o compressR_worker_LOLS compressR_worker_LOLS.c RLEcompress.c

#This rule cleans up executable file


clean: 
	rm -f main
