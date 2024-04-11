#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define FILOSOFOS 5

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t palillos[FILOSOFOS] = { PTHREAD_MUTEX_INITIALIZER };

void * filosofo(void * arg){
    int *id = (int *) arg;
    srand(time(NULL) + *id);

    while(1){
        printf("\nEl Filósofo %d está pensando en ser o no ser\n", *id);
        usleep(2000000);

        printf("El Filósofo %d intenta tomar el palillo de la izquierda %d\n", *id, *id);
        pthread_mutex_lock(&palillos[*id]);
        printf("El Filósofo %d agarró el palillo izquierdo %d\n", *id, *id);

        printf("El Filósofo %d intenta tomar el palillo de la derecha %d\n", *id, (*id + 1) % FILOSOFOS);
        pthread_mutex_lock(&palillos[(*id + 1) % FILOSOFOS]);
        printf("El Filósofo %d agarró el palillo de la derecha %d\n", *id, (*id + 1) % FILOSOFOS);

        printf("El Filósofo %d está comiendo :3 ....\n", *id);
        sleep(rand() % 2 + 1);

        pthread_mutex_unlock(&palillos[*id]); 
        pthread_mutex_unlock(&palillos[(*id + 1) % FILOSOFOS]);
    }
    pthread_exit(NULL);
}

int main(){
    pthread_t filosofos[FILOSOFOS];
    int ids[FILOSOFOS];

    for(int i = 0; i < FILOSOFOS; i++){
        ids[i] = i;
        pthread_create(&filosofos[i], NULL, filosofo, &ids[i]);
    }

    for(int i = 0; i < FILOSOFOS; i++){
        pthread_join(filosofos[i], NULL);
    }

    return 0;
}
