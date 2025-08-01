#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MAX_MESSAGE_SIZE 100

struct message_buffer
{
    long message_type;
    char message_text[MAX_MESSAGE_SIZE];
};

#include <netinet/in.h>
#define BACKLOG 1
#define MAXSENDLEN 1024
#define MAXRECEVLEN 1024

