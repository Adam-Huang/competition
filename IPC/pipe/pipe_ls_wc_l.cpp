#include<stdio.h>
#include<unistd.h>

int main()
{
    int fd[2];  // 两个文件描述符
    pid_t pid;
    char buff[20];
	printf("[line:%d] Parent pid:%d\n",__LINE__,getpid());

    if(pipe(fd) < 0)  // 创建管道
        printf("Create Pipe Error!\n");

    if((pid = fork()) < 0)  // 创建子进程
        printf("Fork Error!\n");
    else if(pid > 0)  // 父进程
    {
		printf("Parent pid:%d fd[0]:%d, fd[1]:%d\n",getpid(),fd[0],fd[1]);
        close(fd[0]); // 关闭读端
		dup2(fd[1],STDOUT_FILENO);
		execlp("ls","ls",NULL);
    }
    else
    {
		printf("Children pid:%d fd[0]:%d, fd[1]:%d\n",getpid(),fd[0],fd[1]);
        close(fd[1]); // 关闭写端
		dup2(fd[0],STDIN_FILENO);
		execlp("wc","wc","-l",NULL);
    }

    return 0;
}