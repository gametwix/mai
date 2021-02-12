#include <stdio.h>
//#include <string.h>
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
    char *filename = NULL;
    getline(filename,NULL,stdin);
    filename[sizeof(filename)-1] = '\0';
    printf("%s",filename);
    //можно ли юзать готовый mutex? | не получится передать)))
    /*pthread_mutex_t lock;
    pthread_mutex_init(&lock, NULL);*/


    int mutex_file = shm_open(MUTEX_NAME, O_RDWR | O_CREAT, S_IRWXU);
    int pipe = shm_open(SH_NAME, O_RDWR | O_CREAT, S_IRWXU);
    int pipe_size = shm_open(SH_NAME_SIZE, O_RDWR | O_CREAT, S_IRWXU);
    //Проверить создание pid shared memory файлов

    ftruncate(pipe, getpagesize());
    ftruncate(pipe, sizeof(int));
    ftruncate(mutex_file, sizeof(pthread_mutex_t));
    //Добавить проверку того, что длина файла успешно изменена 

    int* share_data = (int*) mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, pipe, 0);
    int* share_data_size = (int*) mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, pipe_size, 0);
    pthread_mutex_t* lock = (pthread_mutex_t*) mmap(NULL, sizeof(pthread_mutex_t), PROT_READ | PROT_WRITE, MAP_SHARED, pipe_size, 0);
    //Проверить удачность проекции файла на память

    pthread_mutex_init(lock,NULL); 
    //Проверить удачноcть инициализации mutex'а

    share_data_size = 0;
    int id = fork();
    if(id == 0){
        execl("./child","child",filename,SH_NAME,SH_NAME_SIZE,MUTEX_NAME,(char*) NULL);
    } else {
        int num;
        char ch;
        
        while(scanf("%d%c",&num,&ch) != EOF){
            pthread_mutex_lock(lock);
            share_data[pipe_size] = num;
            ++pipe_size;

            if(ch = '\n'){
                pthread_mutex_unlock(lock);

                //wait child
                while(pipe_size == 0){}
            }
        }
        pthread_mutex_lock(lock);
        pipe_size = -1;
        pthread_mutex_unlock(lock);

    }
    return 0;
}