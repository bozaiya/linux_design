/*
编写一个程序,创建3个线程，假设这3个线程的ID分别为A、B、C
每个线程将自己的ID在屏幕上打印10遍，要求输出结果必须按照ABC顺序显示
如ABCABC...依次递推
*/
#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 3

pthread_t threads[NUM_THREADS];
int thread_ids[NUM_THREADS] = {0, 1, 2};
pthread_attr_t thread_attrs[NUM_THREADS];
pthread_mutex_t mutex;
pthread_cond_t cond;
int current_thread = 0;

void *print_thread_id(void *thread_id)
{
    int tid = *(int *)thread_id;

    for (int i = 0; i < 10; i++)
    {
        pthread_mutex_lock(&mutex);
        while (current_thread != tid)
        {
            pthread_cond_wait(&cond, &mutex);
        }

        printf("%c", 'A' + tid); // 打印线程ID
        fflush(stdout);

        current_thread = (current_thread + 1) % NUM_THREADS;
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

int main()
{
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    // 初始化线程属性
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_attr_init(&thread_attrs[i]);
    }

    // 设置线程优先级
    struct sched_param params[NUM_THREADS];
    params[0].sched_priority = 2; // 线程A优先级
    params[1].sched_priority = 1; // 线程B优先级
    params[2].sched_priority = 0; // 线程C优先级

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_attr_setschedparam(&thread_attrs[i], &params[i]);
    }

    // 创建线程
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&threads[i], &thread_attrs[i], print_thread_id, (void *)&thread_ids[i]);
    }

    // 等待线程完成
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // 销毁线程属性
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_attr_destroy(&thread_attrs[i]);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    printf("\n");
    return 0;
}