#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define ranas 10
#define meta 30
int posicionRanita[ranas]={0};


void * carrera(void * arg){
    int * id = (int *) arg;

    while(posicionRanita[*id] < meta){
        posicionRanita[*id] += rand()%10+1;
        printf("\nLa ranita brincó a la posición: %d", posicionRanita[*id]);
        if(posicionRanita[*id]>=meta){
            printf("\nYo soy la ranita que ganó: %d \n", *id);
        }
        usleep(2000000);
    }
    pthread_exit(NULL);
    
}

int main(){
    srand(time(NULL));
    pthread_t ranitas[ranas]; 

    for(int i=0; i < ranas; i++){
        int id = i;
        pthread_create(&ranitas[i], NULL, carrera, (void *)&id);
    }

    for(int i=0; i < ranas; i++){
        pthread_join(ranitas[i], NULL);
    }

}