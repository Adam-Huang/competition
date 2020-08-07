/*
$ sudo gcc -g -rdynamic backtrace_thread.c add.c dump.c -lpthread -o backtrace
*/
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>	    /* for signal */
#include <execinfo.h> 	/* for backtrace() */
#include <stdio.h>
 
extern void dump(void);
extern void signal_handler(int signo);
extern int add(int num);

#define NUM_THREADS     5
 
void *PrintHello(void *threadid)
{  
	// 对传入的参数进行强制类型转换，由无类型指针变为整形数指针，然后再读取
	int tid = *((int*)threadid), ret = 0;
	printf("[Line: %d]main() : Create thread, tid: %d \n",__LINE__,tid);
	if(tid == 3) {
		sleep(5);
		add(0);
	}
	else{
		while(1);
	}
	
	
}
 
int main ()
{
	signal(SIGSEGV, signal_handler);
	pthread_t threads[NUM_THREADS];
	int indexes[NUM_THREADS];// 用数组来保存i的值
	int rc;
	int i;
	for( i=0; i < NUM_THREADS; i++ ){      
		indexes[i] = i; //先保存i的值 传入的时候必须强制转换为void* 类型，即无类型指针        
		rc = pthread_create(&threads[i], NULL, PrintHello, (void *)&(indexes[i]));
		printf("[Line: %d]main() : Create thread, indexes: %d threads[i]: 0x%llx \n",__LINE__,indexes[i],threads[i]);
		if (rc){
			perror("pthread_create ");
			exit(-1);
		}
	}
	pthread_exit(NULL);
}
/*
(base) ejior@ejior-XPS-8930:~/huangyue2/cmd$ ./backtrace 
[Line: 35]main() : Create thread, indexes: 0 threads[i]: -1471674624 
[Line: 35]main() : Create thread, indexes: 1 threads[i]: -1480067328 
[Line: 35]main() : Create thread, indexes: 2 threads[i]: -1488460032 
[Line: 35]main() : Create thread, indexes: 3 threads[i]: -1496852736 
[Line: 35]main() : Create thread, indexes: 4 threads[i]: -1505245440 
[Line: 20]main() : Create thread, tid: 0 
[Line: 20]main() : Create thread, tid: 1 
[Line: 20]main() : Create thread, tid: 2 
[Line: 20]main() : Create thread, tid: 3 

=========>>>catch signal 11 <<<=========
Dump stack start...
backtrace() returned 8 addresses
  [00] ./backtrace(dump+0x2e) [0x400dfc]
  [01] ./backtrace(signal_handler+0x2e) [0x400efe]
  [02] /lib/x86_64-linux-gnu/libc.so.6(+0x354c0) [0x7ff5a84b64c0]
  [03] ./backtrace(add1+0x1a) [0x400d91]
  [04] ./backtrace(add+0x1c) [0x400dc6]
  [05] ./backtrace(PrintHello+0x58) [0x400c9e]
  [06] /lib/x86_64-linux-gnu/libpthread.so.0(+0x76ba) [0x7ff5a88526ba]
  [07] /lib/x86_64-linux-gnu/libc.so.6(clone+0x6d) [0x7ff5a85884dd]
Dump stack end...
段错误 (核心已转储)
*/

