/*
编写一个多线程程序，计算矩阵5×8中所有元素的和并输出
(例：可创建5个线程，分别计算每行元素的和，主线程中计算5个小计值的和)
*/
#include <iostream>
using namespace std;

int arr[5][8];
int num = 1;
int flag;
int row[5];

void *getSum(void *arg)
{
    for (int j = 0; j < 5; j++)
    {
        row[flag] += arr[flag][j];
    }
}

int main()
{
    int sum = 0;
    pthread_t ntid;

    cout << "初始化矩阵为1-40: " << endl;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            arr[i][j] = num++;
            cout << arr[i][j] << "\t";
        }
        cout << endl;
    }


    //创建线程
    for (flag = 0; flag < 5; flag++)
    {
        int ret = pthread_create(&ntid,NULL,getSum,NULL);
        if (ret != 0)
        {
            cout << "pthread_create error" << endl;
            exit(1);
        }
    }

    //求每行相加
    for (int i = 0; i < 5; i++)
    {
        sum = row[i];
    }

    cout << "总和为：" << sum << endl;
    return 0;
}