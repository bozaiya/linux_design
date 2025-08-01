/*
编写两个线程，其中一个线程接收用户输入，一个线程输出用户输入的数据
使用线程同步方法进行处理，不采用类似sleep(x)的等待语句
*/
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;
pthread_cond_t cond;
int data_ready = 0;
char user_input[100];

void* input_thread(void* arg)
{
    while (1) {
        // 等待用户输入
        printf("请输入数据(按Q退出): ");
        fgets(user_input, sizeof(user_input), stdin);

        // 检查是否要退出
        if (user_input[0] == 'Q' || user_input[0] == 'q')
            break;

        // 加锁，修改共享变量
        pthread_mutex_lock(&mutex);
        data_ready = 1;
        // 发送信号通知输出线程
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

void* output_thread(void* arg)
{
    while (1) {
        // 加锁，等待信号
        pthread_mutex_lock(&mutex);
        while (!data_ready) {
            pthread_cond_wait(&cond, &mutex);
        }
        // 收到信号后打印用户输入的数据
        printf("用户输入的数据是：%s\n", user_input);
        data_ready = 0; // 重置数据准备状态
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

int main()
{
    pthread_t tid_input, tid_output;

    // 初始化互斥锁和条件变量
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    // 创建输入线程和输出线程
    pthread_create(&tid_input, NULL, input_thread, NULL);
    pthread_create(&tid_output, NULL, output_thread, NULL);

    // 等待输入线程结束
    pthread_join(tid_input, NULL);

    // 取消输出线程
    pthread_cancel(tid_output);
    pthread_join(tid_output, NULL);

    // 销毁互斥锁和条件变量
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}