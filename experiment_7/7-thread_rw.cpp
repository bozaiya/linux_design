/*
创建两个子线程
一个子线程（生产者线程）依次向缓冲区写入整数0，1，2，……，19
另一个子线程（消费者线程）暂停3秒后从缓冲区读数，每次读一个，并将读出的数字从缓冲区删除，然后将数字显示出来
副线程等待子线程2（消费者线程）的退出信息，待收集到该信息后，副线程就返回
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 20

int buffer[BUFFER_SIZE];
int count = 0;
int index_producer = 0;
int index_consumer = 0;

void *producer_thread(void *arg)
{
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        while (count == BUFFER_SIZE)
        {
            // 缓冲区已满，等待消费者线程消费数据
            sched_yield();
        }
        buffer[index_producer] = i;
        index_producer = (index_producer + 1) % BUFFER_SIZE;
        count++;
        sched_yield();
    }
    pthread_exit(NULL);
}

void *consumer_thread(void *arg)
{
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        while (count == 0)
        {
            // 缓冲区为空，等待生产者线程产生数据
            sched_yield();
        }
        int value = buffer[index_consumer];
        index_consumer = (index_consumer + 1) % BUFFER_SIZE;
        count--;
        sched_yield();

        printf("Consumer Thread: %d\n", value);
        sleep(3); // 暂停3秒
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t producer_tid;
    pthread_t consumer_tid;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

    pthread_create(&producer_tid, &attr, producer_thread, NULL);
    pthread_create(&consumer_tid, &attr, consumer_thread, NULL);

    pthread_join(producer_tid, NULL);
    pthread_join(consumer_tid, NULL);

    pthread_attr_destroy(&attr);

    return 0;
}