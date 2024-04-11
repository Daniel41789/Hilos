#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define TAMM_ARR 6
int Array[TAMM_ARR] = {0};

void *cuadrado(void *arg) {
    int *id = (int *)arg;
    int inicio = *id * (TAMM_ARR / 2);
    int fin = inicio + (TAMM_ARR / 2);

    for (int i = inicio; i < fin; i++) {
        Array[i] = Array[i] * Array[i];
        printf("\nSoy el hilo %d y he calculado el cuadrado: %d \n", *id, Array[i]);
        usleep(2000000);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t hilo1, hilo2;
    int num = 0;
    for (int i = 0; i < TAMM_ARR; i++) {
        Array[i] = num++;
    }

    int id_hilo1 = 0;
    int id_hilo2 = 1;

    pthread_create(&hilo1, NULL, cuadrado, (void *)&id_hilo1);
    pthread_create(&hilo2, NULL, cuadrado, (void *)&id_hilo2);

    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);
    return 0;
}
