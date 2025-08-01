/*
编写一个程序
在主线程中创建4个新线程，所有线程都输出自己的线程号
*/
#include <iostream>
#include <unistd.h>
using namespace std;

void *printTid(void *arg){
    pthread_t tid;
    tid = pthread_self();
    printf("tid is %lu (0x)%lx\n", tid, tid);
}

int main()
{
    pthread_t ntid;
    //创建线程
    for (int i = 0; i < 4; i++)
    {
        int ret = pthread_create(&ntid,NULL,printTid,NULL);
        if (ret != 0)
        {
            cout << "pthread_create error" << endl;
            exit(1);
        }
    }
    sleep(2);
    exit(0);
}