#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define TAMM_ARR 6
typedef struct parametros{
    int inicio;
    int fin;
} parametros;

int arreglo[TAMM_ARR] = {0};

void *cuadrado(void *arg) {
    parametros * rescatados = (parametros *)arg;
    for(int i = rescatados ->inicio; i < rescatados->fin; i++){
        arreglo[i] = arreglo [i]* arreglo[i];
        sleep(1);
        printf("\nLa posicion %d es: %d \n", i, arreglo[i]);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t hilo1, hilo2;
    parametros argumento1, argumento2;
    argumento1.inicio=0;
    argumento1.fin = TAMM_ARR/2;
    argumento2.inicio = TAMM_ARR/2;
    argumento2.fin = TAMM_ARR;

    for(int i = 0; i < TAMM_ARR; i++){
        arreglo[i] = i;
    }

    pthread_create(&hilo1, NULL, cuadrado, (void*) &argumento1);
    pthread_create(&hilo2, NULL, cuadrado, (void*) &argumento2);

    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    return 0;
}
