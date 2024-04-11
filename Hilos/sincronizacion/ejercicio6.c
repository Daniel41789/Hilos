#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int balance = 0;
#define iteraciones 1000000

void *suma(void * arg){

    for(int i = 0; i < iteraciones; ++i){
        pthread_mutex_lock(&mutex); //bloqueamos el recurso
        balance += 1;
        pthread_mutex_unlock(&mutex); //desbloqueamos el recurso
    }

    pthread_exit(NULL);
}

void *resta(void *arg){
    for(int i = 0; i < iteraciones; ++i){
        pthread_mutex_lock(&mutex);
        balance -= 1;
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

int main(){
    pthread_t sumador, restador;
    pthread_create(&sumador, NULL, suma, NULL);
    pthread_create(&restador, NULL, resta, NULL);

    pthread_join(sumador, NULL);
    pthread_join(restador, NULL);

    printf("\nEl valor balanceado es: %d \n", balance);

    return 0;
}