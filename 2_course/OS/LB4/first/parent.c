#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <pthread.h>

#define SH_NAME "my_shared_mem"
#define SH_NAME_SIZE "my_shared_mem_size"
#define MUTEX_NAME "my_mutex"


int main()
{
    char filename[100];
    scanf("%s",filename);
    printf("%s\n",filename);
    //можно ли юзать готовый mutex? | не получится передать)))
    /*pthread_mutex_t lock;
    pthread_mutex_init(&lock, NULL);*/

    printf("shm_open\n");
    int mutex_file = shm_open(MUTEX_NAME, O_RDWR | O_CREAT, S_IRWXU);
    int pipe = shm_open(SH_NAME, O_RDWR | O_CREAT, S_IRWXU);
    int pipe_size = shm_open(SH_NAME_SIZE, O_RDWR | O_CREAT, S_IRWXU);
    //Проверить создание pid shared memory файлов

    printf("ftruncate\n");
    ftruncate(pipe, getpagesize());
    ftruncate(pipe_size, sizeof(int));
    ftruncate(mutex_file, sizeof(pthread_mutex_t));
    //Добавить проверку того, что длина файла успешно изменена 

    printf("mmap\n");
    int* share_data = (int*) mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, pipe, 0);
    int* share_data_size = (int*) mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, pipe_size, 0);
    pthread_mutex_t* lock = (pthread_mutex_t*) mmap(NULL, sizeof(pthread_mutex_t), PROT_READ | PROT_WRITE, MAP_SHARED, mutex_file, 0);
    //Проверить удачность проекции файла на память

    printf("mutex_init\n");
    pthread_mutex_init(lock,NULL); 
    //Проверить удачноcть инициализации mutex'а

    *share_data_size = 0;
    printf("fork\n");
    int id = fork();
    printf("id=%d\n",id);
    if(id == 0){
        execl("./child","child",filename,SH_NAME,SH_NAME_SIZE,MUTEX_NAME,(char*) NULL);
    } else {
        int num;
        char ch;
        printf("parent\n");
        printf("PARENT LOCK\n");
        pthread_mutex_lock(lock);
        while(scanf("%d%c",&num,&ch) > EOF){
            share_data[*share_data_size] = num;
            ++(*share_data_size);
            printf("send ch=%d\n",ch);
            fflush(stdout);
            if(ch == '\n'){
                printf("PARENT UNLOCK\n");
                pthread_mutex_unlock(lock);
                printf("send shms=%d\n",*share_data_size);
                //wait child
                printf("wait\n");
                while(*share_data_size != 0){}
                printf("send end=%d\n",*share_data_size);
                printf("PARENT LOCK\n");
                pthread_mutex_lock(lock);
            }
        }
        printf("exit\n");
        printf("PARENT UNLOCK\n");
        pthread_mutex_unlock(lock);
        printf("PARENT LOCK\n");
        pthread_mutex_lock(lock);
        *share_data_size = -1;
        printf("PARENT UNLOCK\n");
        pthread_mutex_unlock(lock);
        printf("wait\n");
        while(*share_data_size != 0){}
    }
    return 0;
}