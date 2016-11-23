#include "compressRT.h"

#include "/usr/src/kernels/3.10.0-327.22.2.el7.x86_64/include/linux/poison.h"
#include "/usr/src/kernels/3.10.0-327.22.2.el7.x86_64/include/linux/list.h"
#include "/usr/src/kernels/3.10.0-327.22.2.el7.x86_64/include/linux/module.h"
#include "/usr/src/kernels/3.10.0-327.22.2.el7.x86_64/include/linux/kernel.h"
#include "/usr/src/kernels/3.10.0-327.22.2.el7.x86_64/include/linux/kthread.h"
#include "/usr/src/kernels/3.10.0-327.22.2.el7.x86_64/include/linux/sched.h"

void compressK_LOLS(char * filename, int threadCount){

   FILE *fp;
  struct task_struct *ts; = (struct task_struct *)malloc(sizeof( struct task_struct *)*threadCount);
   long length;
   fp = fopen(filename, "r");

   if(!fp) printf("File not found1\n");
   else{
   		fseek(fp, 0L, SEEK_END);
   		length = ftell(fp)-1;
   		//printf("the file's length is %1dB\n", length);
   		rewind(fp);
   }
   if(threadCount>length){
   		printf("Can not create more threads then there are characters in file");
   		exit(1);
   }
   int remainder = length % threadCount;
   int threadLength = (length - remainder) / threadCount;

   int i;
   int offset=0;
workInfo * work;
   for(i=0; i<threadCount; i++){
   		work= malloc(sizeof(workInfo));
   		work->filename = filename;
   		work->partID = i;
   		work->numPart = threadCount;

   		if(i==0){
   			work->length = threadLength + remainder;
   			work->offset=offset;
   			offset += work->length;
   		}
   		else {
   			work->length = threadLength;
   			work->offset = offset;
   			offset+=work->length; 
   		}
   		// printf("Offset: %d\n", work->offset);
   		ts[i]=kthread_run(&RLEcompress, (void *)work, "Test");
   }
   for(i=0; i<threadCount; i++){
   		kthread_stop(ts[i]);
   }

	free(ts);
	fclose(fp);
	return;
}
