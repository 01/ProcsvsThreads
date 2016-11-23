README

The core source files that can be used to run our project include:

compressT_LOLS.c
compressR_LOLS.c
compressK_LOLS.c
compressR_worker_LOLS.c
compressRT.h
RLEcompress.c
main.c (optional)
makefile (optional)

The easiest way to run our project is to call either the "compressR_LOLS" function or the "compressR_LOLS" function from the main.c file with the appropriate arguments. The provided makefile will create the "main" and "compressR_worker_LOLS" executable files, the latter of which is required by the "compressR_LOLS" function, which calls the "execvp" function to run the worker program. Any main can be used and can call the functions.

Alternatively, call the "compressR_LOLS" and "compressT_LOLS" functions from your own program. Note that the compressRT.h header file and the RLEcompress.c source file contain code needed for the "compressR_LOLS" and "compressT_LOLS" functions.

Our test cases can be found in testplan.txt and time tests can be found in timetests.pdf.

A couple of important notes on our project:

Our program considers it to be an error for the user to request more compression parts (processes or threads) than there are characters in the given input file, throwing an error message and exiting the program in such a case.

If the user enters an incorrect file name (not matching any given input file) the program will print an error message and exit.

The program must be run with at least one compression part (process or thread). Otherwise, it will print an error message and exit.

If the number of characters in the input file does not divide evenly among multiple compression parts, the remainder will be added to the first part.

compressK_LOLs.c will only work on systems that have the Linux Kernel Headers build complete to allow #include <linux/example.h>
CompressK will call kernel level threads as opposed to user level threads. Kernel threads are scheduled by the kernel and are slow to create and manage as it has to be scheduled on a kernel level. Would have been able to shown it in our timetest.pdf but did not have proper access to run kernel code on ilabs.
