#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/* En este problema, vamos a simular una biblioteca donde m ultiples personas pueden leer libros
al mismo tiempo, pero solo una persona puede escribir comentarios o modificar un libro a la vez. 
Los lectores pueden leer libros simult ́aneamente, pero cuando alguien está libro
en un libro, ningún otro puede leer o escribir hasta que se complete la escritura.
*/ 
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
bool libro = false; // true o false es para ver si se está escribiendo en el libro
pthread_cond_t cond_prod = PTHREAD_COND_INITIALIZER;

void * lectores(void * arg){
    int *id = (int *) arg;

    for(int i = 0; i < 3; i++){
        sleep(2);
        
        int num = (int)rand()%4;
        if(num != 0){
            libro = true;
        }
        
        if(!libro){
            printf("\nHola, soy el hilo %d y estoy leyendo el libro xD", *id);
        }else{
            printf("\nHola, soy el hilo %d y no puedo hacer nada :(", *id);
            
        }
        
        sleep(2);
    }

    pthread_exit(NULL);
}

void * escritores(void * arg){
    int *id = (int *) arg;

    for(int i = 0; i < 3; i++){
        pthread_mutex_lock(&mutex);
        libro = true;
        printf("\nHola, soy el hilo %d y estoy escribiendo", *id);
        sleep(2);
        libro = false;
        
        pthread_mutex_unlock(&mutex);
        sleep(2);
    }

    pthread_exit(NULL);
}

int main(){
    pthread_t hilo1, hilo2, hilo3, escritor;
    srand(time(NULL));
    int id_hilo1 = 1, id_hilo2 = 2, id_hilo3 = 3;
    int id_escritor = 4;

    pthread_create(&escritor, NULL, escritores, (void *)&id_escritor);

    pthread_create(&hilo1, NULL, lectores, (void *)&id_hilo1);
    pthread_create(&hilo2, NULL, lectores, (void *)&id_hilo2);
    pthread_create(&hilo3, NULL, lectores, (void *)&id_hilo3);
    

    pthread_join(escritor, NULL);

    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);
    pthread_join(hilo3, NULL);
    
    
    return 0;
}