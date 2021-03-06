#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>

static void sig_child(int signo);
pid_t waitpid(pid_t pid, int *status, int options);

int main()
{
    pid_t pid;
    //创建捕捉子进程退出信号
	int i = 3;
    signal(SIGCHLD,sig_child);
    pid = fork();
    if (pid < 0)
    {
        perror("fork error:");
        exit(1);
    }
    else if (pid == 0)
    {
        while(i >0){
			printf("I am child process,pid id %d.I will exit at %d sec later. \n",getpid(),i--);
			sleep(1);
		}
		return 44;
        //exit(0);
    }
    printf("I am father process.I will sleep two seconds\n");
    //等待子进程先退出
    sleep(7);
    //输出进程信息
    system("ps -o pid,ppid,state,tty,command");
    printf("father process is exiting.\n");
    return 0;
}

static void sig_child(int signo)
{
    pid_t        pid;
    int        stat;
    //处理僵尸进程
    while ((pid = waitpid(-1, &stat, WNOHANG)) >0)
            printf("[Line %d] child:%d state:%d terminated.\n", __LINE__,pid,stat);
	// 用宏看看子进程是如何终止的
	if(WIFEXITED(stat) > 0) {
		printf("[Line %d] return:%d\n", __LINE__, WEXITSTATUS(stat));
	}
	if(WIFSIGNALED(stat) > 0){
		printf("[Line %d] killed by:%d\n", __LINE__, WTERMSIG(stat));
	}
}
