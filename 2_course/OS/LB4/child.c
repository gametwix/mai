#include "stdio.h"
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <pthread.h>


int main(int argc,char *argv[]){
    long long sum = 0;
    int num;
    char ch;
    FILE *file;
    char *filename = argv[1];
    char *sh_name = argv[2];
    char *sh_size_name = argv[3];
    char *mutex_name = argv[4]; 
    file = fopen(filename, "w");

    int mutex_file = shm_open(mutex_name, O_RDWR | O_CREAT, S_IRWXU);
    int pipe = shm_open(sh_name, O_RDWR | O_CREAT, S_IRWXU);
    int pipe_size = shm_open(sh_size_name, O_RDWR | O_CREAT, S_IRWXU);


    int* share_data = (int*) mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, pipe, 0);
    int* share_data_size = (int*) mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, pipe_size, 0);
    pthread_mutex_t* lock = (pthread_mutex_t*) mmap(NULL, sizeof(pthread_mutex_t), PROT_READ | PROT_WRITE, MAP_SHARED, pipe_size, 0);

    while(*share_data_size != -1){
        if(*share_data_size > 0){
            pthread_mutex_lock(lock);
            for(int i = 0;i < *share_data_size; ++i){
                sum += share_data[i];
            }
            fprintf(file,"%lld\n",sum);
            sum = 0;
            share_data_size = 0;
            pthread_mutex_unlock(lock);
        }
    }
    fclose(file);
    return 0;
}

