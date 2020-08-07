/*
 *   $ sudo gcc -g -rdynamic backtrace.c add.c dump.c -o backtrace
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>	    /* for signal */
#include <execinfo.h> 	/* for backtrace() */
 
extern void dump(void);
extern void signal_handler(int signo);
extern int add(int num);
 
int main(int argc, char *argv[])
{
	int sum = 0x00;
	
	signal(SIGSEGV, signal_handler);  /* 为SIGSEGV信号安装新的处理函数 */
	
	// 多线程情况，会打印每个线程的堆栈嘛
	
	
	sum = add(sum);
	
	printf(" sum = %d \n", sum);
	
	return 0x00;
}