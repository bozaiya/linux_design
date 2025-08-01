/*
编写一个多线程程序来计算一个4*10矩阵中所有元素的和并输出结果
其中由4个线程分别将矩阵每一行的数据加入累加器，由互斥锁控制累加器的互斥使用
主线程输出最终结果
*/

#include <iostream>
#include <unistd.h>
using namespace std;
#define N 4

pthread_mutex_t mutex;
double array[4][10], sum = 0;

int row = 0;    //行

void *getSum(void *arg)
{
    // 加锁
    pthread_mutex_lock(&mutex);
    // 临界资源互斥使用
    for (int j = 0; j < 10; j++)
    {
        sum += array[row][j];
    }
    row++;
    // 释放锁
    pthread_mutex_unlock(&mutex);
}

int main()
{
    pthread_t ptr[N];

    cout << "四行十列的矩阵为：(个位代表第几行，小数代表第几列)" << endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            array[i][j] = (i + 1 ) + ((double)j/10 + 0.1);
            cout << "\t" << array[i][j];
        }
        cout << endl;
    }
    
    // 创建线程
    for (int i = 0; i < N; i++)
    {
        int ret = pthread_create(&ptr[i], NULL, getSum, NULL);
        if (ret != 0)
        {
            perror("create failed");
        }
    }

    // 等待线程结束
    for (int i = 0; i < N; i++)
    {
        pthread_join(ptr[i], NULL);
    }

    cout << "所有元素的和为：" << sum << endl;
    pthread_mutex_destroy(&mutex);
    return 0;
}