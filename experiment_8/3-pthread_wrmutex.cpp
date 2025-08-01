/*
将一个文件中的内容写入到另一个空白文件中
(读与写的操作分别在两个线程中完成传送数据使用共享内存实现)
要求文件内容的大小要远大于所用共享内存的大小
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#define SHM_SIZE 1024

void* writer_thread(void* arg) {
    int shmid = *((int*)arg);
    const char* input_file = "file_1";

    char* shmaddr = (char*)shmat(shmid, NULL, 0);
    if (shmaddr == (char*)-1) {
        perror("shmat");
        exit(1);
    }

    int input_fd = open(input_file, O_RDONLY);
    if (input_fd == -1) {
        perror("open");
        exit(1);
    }

    ssize_t bytes_read = read(input_fd, shmaddr, SHM_SIZE);
    if (bytes_read == -1) {
        perror("read");
        exit(1);
    }

    if (shmdt(shmaddr) == -1) {
        perror("shmdt");
        exit(1);
    }

    if (close(input_fd) == -1) {
        perror("close");
        exit(1);
    }

    pthread_exit(NULL);
}

void* reader_thread(void* arg) {
    int shmid = *((int*)arg);
    const char* output_file = "file_2";

    char* shmaddr = (char*)shmat(shmid, NULL, 0);
    if (shmaddr == (char*)-1) {
        perror("shmat");
        exit(1);
    }

    int output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (output_fd == -1) {
        perror("open");
        exit(1);
    }

    ssize_t bytes_written = write(output_fd, shmaddr, SHM_SIZE);
    if (bytes_written == -1) {
        perror("write");
        exit(1);
    }

    if (shmdt(shmaddr) == -1) {
        perror("shmdt");
        exit(1);
    }

    if (close(output_fd) == -1) {
        perror("close");
        exit(1);
    }

    pthread_exit(NULL);
}

int main() {
    key_t key = ftok(".", 'S');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    pthread_t writer_tid, reader_tid;

    if (pthread_create(&writer_tid, NULL, writer_thread, (void*)&shmid) != 0) {
        perror("pthread_create");
        exit(1);
    }

    if (pthread_create(&reader_tid, NULL, reader_thread, (void*)&shmid) != 0) {
        perror("pthread_create");
        exit(1);
    }

    if (pthread_join(writer_tid, NULL) != 0) {
        perror("pthread_join");
        exit(1);
    }

    if (pthread_join(reader_tid, NULL) != 0) {
        perror("pthread_join");
        exit(1);
    }

    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }

    return 0;
}