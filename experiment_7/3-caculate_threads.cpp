/*
使用多线程编写矩阵乘法程序
给定两个矩阵A和B
其中矩阵A为m行、k列，B为k行，n列，A和B的矩阵乘积为C,C为m行、n列
对于该程序计算，每个Cij是一个独立的线程工作，既使用M×N个工作线程完成
*/

#include <iostream>
#include <unistd.h>
using namespace std;
#define M 3
#define K 3
#define N 3

int arr1[M][K];
int arr2[K][N];
int result_arr[M][N];

int row = 0, col = 0;  //第几行的数字开始乘法,第几列的数字开始乘法

void *getMulti(void *arg)
{
    //第row行x第col列
    for (int i = 0; i < K; i++)
    {
        result_arr[row][col] += arr1[row][i] * arr2[i][col];
    }
}

int main()
{
    pthread_t ntid;
   //初始化
    int begin = 1;

    cout << "矩阵1为:" << endl;
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < K; j++)
        {
            arr1[i][j] = begin++;
            cout << arr1[i][j] << "\t";
        }
        cout << endl;
    }

    begin = 1;
    cout << "矩阵2为:" << endl;
    for (int i = 0; i < K; i++)
    {
        for (int j = 0; j < N; j++)
        {
            arr2[i][j] = begin++;
            cout << arr1[i][j] << "\t";
        }
        cout << endl;
    }

    // 创建MxN个线程
    for (int i = 0; i < M*N; i++)
    {
        int ret = pthread_create(&ntid, NULL, getMulti, NULL);
        if (ret != 0)
        {
            cout << "pthread_create error" << endl;
            exit(1);
        }
        col++;
        col %= N;
        if(col == 0)
        {
            row++;
            row %= M;
        }
        sleep(0.2);
    }

    cout << "矩阵相乘的结果为:" << endl;
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << result_arr[i][j] << "\t";
        }
        cout << endl;
    }
    return 0;
}