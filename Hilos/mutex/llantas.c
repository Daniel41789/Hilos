#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int almacen = 0; // El almacen está vacío
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condicion = PTHREAD_COND_INITIALIZER;

void * chamba(void * arg){
    int *id = (int *) arg;
    while(1){
        pthread_mutex_lock(&mutex);
        while(almacen == 0){
            pthread_cond_wait(&condicion, &mutex);
        }

        printf("\nEl trabajador %d se gastó la pieza y tengo %d piezas\n", *id, almacen);
        almacen--;
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    pthread_exit(NULL);
}

void * llena(void * arg){
    int *id = (int *) arg;
    while(1){
        pthread_mutex_lock(&mutex);
        printf("\nEl proveedor %d esta poniendo una pieza y tengo %d piezas\n", *id, almacen);
        almacen++;
        pthread_cond_signal(&condicion);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    pthread_exit(NULL);
}

int main(int argc, char * argv[]){
    int num_trabajadores = atoi(argv[1]);
    int num_proveedores = atoi(argv[2]);
    pthread_t trabajadores[num_trabajadores]; // arreglo de hilos
    pthread_t proveedores[num_proveedores];
    int id_t[num_trabajadores];
    int id_p[num_proveedores];

    for(int i=0; i < num_trabajadores; i++){
        id_t[i] = i + 1; 
        pthread_create(&trabajadores[i], NULL, chamba, (void *)&id_t[i]);
    }

    for(int i = 0; i < num_proveedores; i++){
        id_p[i] = i+1;
        pthread_create(&proveedores[i], NULL, llena, (void *)&id_p[i]);
    }

    // esperamos a los hilos
    for(int i=0; i < num_trabajadores; i++){
        pthread_join(trabajadores[i], NULL);
    }

    for(int i = 0; i < num_proveedores; i++){
       pthread_join(proveedores[i], NULL);
    }

}