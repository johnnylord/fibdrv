#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define FIB_DEV "/dev/fibonacci"
#define THREADS 5
#define OFFSET 100

void *thread_task(void *data)
{
    int fd, i;
    unsigned long long sz;
    fd = open(FIB_DEV, O_RDWR);

    if (fd < 0) {
        perror("Failed to open character device");
        pthread_exit(NULL);
    }

    char kbuffer[100];
    for (i = OFFSET; i >= 0; i--) {
        lseek(fd, i, SEEK_SET);
        sz = read(fd, kbuffer, 1);
        printf("Reading from " FIB_DEV
               " at offset %d, returned the sequence "
               "%lld.\n",
               i, sz);
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t t[THREADS];
    for (int i = 0; i < THREADS; ++i) {
        pthread_create(&t[i], NULL, thread_task, NULL);
    }
    for (int i = 0; i < THREADS; ++i) {
        pthread_join(t[i], NULL);
    }
    return 0;
}
