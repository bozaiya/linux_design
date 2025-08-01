/*
编写一个包含两个线程的程序
在主线程中接收键盘输入，并将输入的字符放入缓冲区中
缓冲区满后,由另一个线程输出缓冲区的内容，用互斥锁实现二者间的同步。
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

#define MAX_LENGTH 11
char buffer[MAX_LENGTH];

pthread_mutex_t mutex;
pthread_cond_t empty;
pthread_cond_t notempty;

void *Input(void *arg)
{
    char tempbuffer[MAX_LENGTH];
    // 获取锁
    pthread_mutex_lock(&mutex);
    pthread_cond_wait(&empty, &mutex);
    // 临界资源
    printf("请输入内容(10个字符): ");
    for (int i = 0; i < MAX_LENGTH; i++)
    {
        scanf("%c", &buffer[i]);
    }
    memcpy(tempbuffer, buffer, MAX_LENGTH);
    // 释放锁
    pthread_cond_signal(&notempty);
    pthread_mutex_unlock(&mutex);
}

void *Output(void *arg)
{
    // 获取锁
    pthread_mutex_lock(&mutex);
    pthread_cond_wait(&notempty, &mutex);
    // 临界资源
    printf("%s\n", buffer);
    // 释放锁
    pthread_cond_signal(&empty);
    pthread_mutex_unlock(&mutex);
}

int main()
{
    pthread_t ptr[2];

    // 初始化互斥锁
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&empty, NULL);
    pthread_cond_init(&notempty, NULL);

    // 创建输入线程
    pthread_create(&ptr[0], NULL, Input, NULL);

    // 创建输出线程
    pthread_create(&ptr[1], NULL, Output, NULL);

    sleep(1);

    pthread_cond_signal(&empty);

    for (int i = 0; i < 2; i++)
    {
        pthread_join(ptr[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&empty);
    pthread_cond_destroy(&notempty);

    exit(EXIT_SUCCESS);
}