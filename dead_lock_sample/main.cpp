#include <stdio.h>

#include <unistd.h>
#include <pthread.h>

// *) 引入该头文件即可, 不需要在修改任何代码了
#include "dead_lock_stub.h"

pthread_mutex_t mutex_1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_2 = PTHREAD_MUTEX_INITIALIZER;

void *thread_rountine_1(void *args)
{
    pthread_mutex_lock(&mutex_1);
    sleep(1);
    pthread_mutex_lock(&mutex_2);

    pthread_mutex_unlock(&mutex_2);
    pthread_mutex_unlock(&mutex_1);
    return (void *)(0);
}

void *thread_rountine_2(void *args)
{
    pthread_mutex_lock(&mutex_2);
    sleep(1);
    pthread_mutex_lock(&mutex_1);

    pthread_mutex_unlock(&mutex_1);
    pthread_mutex_unlock(&mutex_2);
    return (void *)(0);
}

int main()
{

    // *) 添加该行， 表示启动死锁检测功能 
    DeadLockGraphic::getInstance().start_check();

    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, thread_rountine_1, NULL);
    pthread_create(&tid2, NULL, thread_rountine_2, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    return 0;
}

