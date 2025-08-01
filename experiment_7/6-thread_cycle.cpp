/*
编程实现创建一个线程，子线程循环10次，接着主线程循环100次
子线程再循环10次，接主线程又循环100次，如此。反复循环50次
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_ITERATIONS 50
#define SUB_THREAD_ITERATIONS 10
#define MAIN_THREAD_ITERATIONS 100

int counter = 0;

void* sub_thread_function(void* arg) {
    for (int i = 0; i < SUB_THREAD_ITERATIONS; i++) {
        while (counter % 2 != 0) {
            // 等待主线程完成
            pthread_yield();
        }
        printf("Sub Thread: %d\n", i);
        counter++;
    }
    pthread_exit(NULL);
}

void* main_thread_function(void* arg) {
    for (int i = 0; i < MAIN_THREAD_ITERATIONS; i++) {
        while (counter % 2 == 0) {
            // 等待子线程完成
            pthread_yield();
        }
        printf("Main Thread: %d\n", i);
        counter++;
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t sub_thread;
    pthread_t main_thread;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

    for (int i = 0; i < NUM_ITERATIONS; i++) {
        pthread_create(&sub_thread, &attr, sub_thread_function, NULL);
        pthread_create(&main_thread, &attr, main_thread_function, NULL);

        pthread_join(sub_thread, NULL);
        pthread_join(main_thread, NULL);
    }

    pthread_attr_destroy(&attr);

    return 0;
}