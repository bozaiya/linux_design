#include <stdio.h>

int main()
{
    int choice;
    scanf("%d",&choice);
    int flag = 1;
    while (flag)
    {
        switch (choice)
        {
        case 1:
            printf("hello");
            flag = 0;
            break;
        case 2:
            printf("nihao");
            flag = 0;
            break;

        case 3:
            printf("shijie");
            flag = 0;
            break;

        case 4:
            flag = 0;
            break;
        }
    }
    return 0;
}