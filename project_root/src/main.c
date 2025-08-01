#include <stdlib.h>
#include <pthread.h>
#include "list_pid.h"

extern void function_list();
extern void function_operate();
extern void funciton_communicate();

int main()
{
    int symbol = 1;
    int choice = 0;

    while (symbol)
    {
        printf("----MAIN MENU----\n");
        printf("*1.当前运行的进程及详细信息*\n");
        printf("*2.进程操作*\n");
        printf("*3.进程通信*\n");
        printf("*4.退出*\n");
        printf("~: ");
        
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            function_list();
            break;

        case 2:
            function_operate();
            break;

        case 3:
            funciton_communicate();
            break;

        case 4:
            symbol = 0;
            break;
        }
    }

    return 0;
}
