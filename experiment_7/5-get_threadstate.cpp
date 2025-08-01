/*
编写一个程序
在主线程中创建一个新线程，在主线程中得到的新线程的各个属性，并在主线程中将它打印输出
*/
#include <iostream>
#include <unistd.h>
using namespace std;

void display_pthread_attr(pthread_attr_t *attr)
{
    int s, i;
    size_t v;
    void *stkaddr;
    struct sched_param sp;
    // 获取分离状态
    s = pthread_attr_getdetachstate(attr, &i);
    if (s != 0)
    {
        cout << "getdetachstate failed" << endl;
        exit(EXIT_FAILURE);
    }
    printf("\tDetach state: %s\n",(i == PTHREAD_CREATE_DETACHED)?"PTHREAD_CREATE_DETACHED":(i == PTHREAD_CREATE_JOINABLE)?"PTHREAD_CREATE_JOINABLE":"???");

    // 获取作用域
    s = pthread_attr_getscope(attr, &i);
    if (s != 0)
    {
        cout << "getscope failed" << endl;
        exit(EXIT_FAILURE);
    }
    printf("\tScope state: %s\n",(i == PTHREAD_SCOPE_SYSTEM)?"PTHREAD_SCOPE_SYSTEM":(i == PTHREAD_SCOPE_PROCESS)?"PTHREAD_SCOPE_PROCESS":"???");


    // 获取继承状态
    s = pthread_attr_getinheritsched(attr, &i);
    if (s != 0)
    {
        cout << "getinheritsched failed" << endl;
        exit(EXIT_FAILURE);
    }
    printf("\tInherit scheduler state: %s\n",(i == PTHREAD_INHERIT_SCHED)?"PTHREAD_INHERIT_SCHED":(i == PTHREAD_EXPLICIT_SCHED)?"PTHREAD_EXPLICIT_SCHED":"???");

    // 获取调度策略
    s = pthread_attr_getschedpolicy(attr, &i);
    if (s != 0)
    {
        cout << "getschedpolicy failed" << endl;
        exit(EXIT_FAILURE);
    }
    printf("\tscheduling policy state: %s\n",(i == SCHED_OTHER)?"SCHED_OTHER":(i == SCHED_FIFO)?"SCHED_FIFO":(i == SCHED_RR)? "SCHED_RR":"???");

    // 获取调度参数
    s = pthread_attr_getschedparam(attr, &sp);
    if (s != 0)
    {
        cout << "getschedparam failed" << endl;
        exit(EXIT_FAILURE);
    }
    printf("\tScheduling priority state: %d\n", sp.sched_priority);

    // 获取线程栈末尾警戒缓冲区大小
    s = pthread_attr_getguardsize(attr, &v);
    if (s != 0)
    {
        cout << "getschedparam failed" << endl;
        exit(EXIT_FAILURE);
    }
    printf("\tGuardsize state: %d bytes\n",v);

    // 获取栈
    s = pthread_attr_getstack(attr, &stkaddr, &v);
    if (s != 0)
    {
        cout << "getschedparam failed" << endl;
        exit(EXIT_FAILURE);
    }
    printf("\tStack address: %p\n",stkaddr);
    printf("\tStack size: 0x%zx bytes\n", v);
}

void *getState(void *arg)
{
    pthread_attr_t gattr;
    int s;
    s = pthread_getattr_np(pthread_self(), &gattr);

    if (s != 0)
    {
        perror("errror");
        exit(EXIT_FAILURE);
    }

    cout << "Thread attributes are:" << endl;
    display_pthread_attr(&gattr);
    exit(EXIT_SUCCESS);
}

int main()
{
    int s;
    pthread_attr_t attr;
    pthread_t thr;

    s = pthread_attr_init(&attr);
    if (s != 0)
    {
        cout << "init failed" << endl;
        exit(EXIT_FAILURE);
    }
    
    // 创建线程
    int ret = pthread_create(&thr, &attr, getState, NULL);
    if (ret != 0)
    {
        cout << "pthread_create error" << endl;
        exit(1);
    }
    if (&attr != NULL)
    {
        s = pthread_attr_destroy(&attr);
        if (s != 0)
        {
            cout << "destroy failed" << endl;
            exit(EXIT_FAILURE);
        }
    }
    pause();    //其他线程调用exit()结束
}
