/*
编写一个包含2个线程的程序，在主程序中创建一个全局变量并初始化为0
在另一个线程中对这个全局变量进行累加运算，并在结束时向主线程返回一个结果
在主线程中打印输出
*/

#include <iostream>
#include <unistd.h>
using namespace std;

int sum = 0;

void *getSum(void *arg)
{
    for (int i = 0; i < 10; i++)
    {
        if (i < 9)
        {
            cout << i << "+";
        }else{
            cout << i << endl;
        }
        sum += i;
    }
    char *result = "---success---";
    pthread_exit((void*) result);
}

int main()
{
    pthread_t ptr;
    void *pth_join_ret;
    pthread_create(&ptr, NULL, getSum, NULL);

    pthread_join(ptr, &pth_join_ret);

    cout << (char*)pth_join_ret << endl;
    cout << "结果为：" << sum << endl;
    return 0;
}