#include "stdio.h"
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <pthread.h>


int main(int argc,char *argv[]){
    printf("child\n");
    long long sum = 0;
    int num;
    char ch;
    FILE *file;
    char *filename = argv[1];
    char *sh_name = argv[2];
    char *sh_size_name = argv[3];
    char *mutex_name = argv[4];
    printf("%s\n",mutex_name);
    printf("file open\n");
    file = fopen(filename, "w");

    printf("shm_open\n");
    int mutex_file = shm_open(mutex_name, O_RDWR | O_CREAT, S_IRWXU);
    int pipe = shm_open(sh_name, O_RDWR | O_CREAT, S_IRWXU);
    int pipe_size = shm_open(sh_size_name, O_RDWR | O_CREAT, S_IRWXU);

    printf("mmap\n");
    int* share_data = (int*) mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, pipe, 0);
    int* share_data_size = (int*) mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, pipe_size, 0);
    pthread_mutex_t* lock = (pthread_mutex_t*) mmap(NULL, sizeof(pthread_mutex_t), PROT_READ | PROT_WRITE, MAP_SHARED, mutex_file, 0);

    printf("%d\n",*share_data_size);
    while(*share_data_size != -1){
        printf("share_data_size = %d\n",*share_data_size);
        printf("CHILD LOCK\n");
        pthread_mutex_lock(lock);
        printf("share_data_size = %d\n",*share_data_size);
        if((*share_data_size) > 0){
            printf("share_data_size = %d\n",*share_data_size);
            for(int i = 0;i < *share_data_size; ++i){
                sum += share_data[i];
            }
            printf("sum = %lld\n",sum);
            printf("share_data_size = %d\n",*share_data_size);
            //fprintf(file,"%lld\n",sum);
            sum = 0;
            *share_data_size = 0;
        }
        printf("CHILD UNLOCK\n");
        pthread_mutex_unlock(lock);
    }
    printf("child exit\n");
    fclose(file);
    *share_data_size = 0;
    return 0;
}

