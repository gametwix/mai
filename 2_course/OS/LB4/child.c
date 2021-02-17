#include "stdio.h"
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <pthread.h>


int main(int argc,char *argv[]){
    //Read args
    if(argc < 5){
        printf("Arguments error");
        return 1;
    }
    char *filename = argv[1];
    char *sh_data_name = argv[2];
    char *sh_data_size_name = argv[3];
    char *mutex_name = argv[4];

    //Open shared memory
    //Create fd shared file
    int fd_shared_data = shm_open(sh_data_name, O_RDWR | O_CREAT, S_IRWXU);
    int fd_shared_data_size = shm_open(sh_data_size_name, O_RDWR | O_CREAT, S_IRWXU);
    int fd_mutex = shm_open(mutex_name,O_RDWR | O_CREAT, S_IRWXU);
    //Map shared files in memory
    int *Data = (int*) mmap(NULL,getpagesize(),PROT_READ | PROT_WRITE, MAP_SHARED, fd_shared_data, 0);
    int *Size = (int*) mmap(NULL,sizeof(int),PROT_READ | PROT_WRITE, MAP_SHARED, fd_shared_data_size, 0);
    pthread_mutex_t *Lock = (pthread_mutex_t*) mmap(NULL,sizeof(pthread_mutex_t*),PROT_READ | PROT_WRITE, MAP_SHARED,fd_mutex,0);
    //Program
    FILE *file;
    file = fopen(filename,"w");
    while ((*Size) != -1){
        pthread_mutex_lock(Lock);
        if(*Size > 0){
            long long sum = 0;
            for(int i = 0;i < *Size; ++i){
                sum += Data[i];
            }
            *Size = 0;
            fprintf(file,"%lld\n",sum);
        }
        pthread_mutex_unlock(Lock);
    }

    fclose(file);
    //~Program
    //Close shared memory
    //Unmap memory
    munmap(Data,getpagesize());
    munmap(Size,sizeof(int));
    munmap(Lock,sizeof(pthread_mutex_t*));
    //Close fd shared memory
    close(fd_shared_data);
    close(fd_shared_data_size);
    close(fd_mutex);
    //Unlick shared memory;
    shm_unlink(sh_data_name);
    shm_unlink(sh_data_size_name);
    shm_unlink(mutex_name);
    return 0;
}

