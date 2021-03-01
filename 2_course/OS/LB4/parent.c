#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <pthread.h>

#define SH_NAME "my_shared_mem"
#define SH_SIZE_NAME "my_shared_mem_size"
#define MUTEX_NAME "my_mutex"



void wait(int *elem, int num){
    while (*elem != num){
        //printf("%d\n",*elem);
    }
}

int main()
{
    //Create shared memory
    //Create fd shared file
    int fd_shared_data = shm_open(SH_NAME, O_RDWR | O_CREAT, S_IRWXU);
    int fd_shared_data_size = shm_open(SH_SIZE_NAME, O_RDWR | O_CREAT, S_IRWXU);
    int fd_mutex = shm_open(MUTEX_NAME,O_RDWR | O_CREAT, S_IRWXU);
    //Resize shared file
    ftruncate(fd_shared_data,getpagesize());
    ftruncate(fd_shared_data_size,sizeof(int));
    ftruncate(fd_mutex,sizeof(pthread_mutex_t*));
    //Map shared files in memory
    int *Data = (int*) mmap(NULL,getpagesize(),PROT_READ | PROT_WRITE, MAP_SHARED, fd_shared_data, 0);
    int *Size = (int*) mmap(NULL,sizeof(int),PROT_READ | PROT_WRITE, MAP_SHARED, fd_shared_data_size, 0);
    pthread_mutex_t *Lock = (pthread_mutex_t*) mmap(NULL,sizeof(pthread_mutex_t*),PROT_READ | PROT_WRITE, MAP_SHARED,fd_mutex,0);
    //Get shared mutex
    pthread_mutexattr_t MutexAttribute;
    pthread_mutexattr_setpshared(&MutexAttribute, PTHREAD_PROCESS_SHARED);
    //Init Size and Lock
    *Size = 0;
    pthread_mutex_init(Lock,&MutexAttribute);    
    //Program
    //Read filename
    char *filename = NULL;
    size_t sizename = 0;
    getline(&filename,&sizename,stdin);
    filename[strlen(filename)-1] = '\0';
    //Fork
    int id = fork();
    //Chouse who are me
    if(id == 0)
        //Child
        execl("./child","child",filename,SH_NAME,SH_SIZE_NAME,MUTEX_NAME,(char*) NULL);
    else{
        //Parent
        int num;
        char sym;
        pthread_mutex_lock(Lock);
        while(scanf("%d%c",&num,&sym) > 0){
            Data[*Size] = num;
            *Size += 1;
            if(sym == '\n'){
                pthread_mutex_unlock(Lock);
                wait(Size,0);
                pthread_mutex_lock(Lock);
            }
        }
        *Size = -1;
        pthread_mutex_unlock(Lock);
    }
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
    shm_unlink(SH_NAME);
    shm_unlink(SH_SIZE_NAME);
    shm_unlink(MUTEX_NAME);

    return 0;
}


