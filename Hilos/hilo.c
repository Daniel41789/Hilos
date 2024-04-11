#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // Para procesos del S.O. (sleep)

int counter; // Variable global que va a compartir el proceso (hilo) principal

void * muestraContador(void * arg){ // estas funciones y sus argumentos necesitan ser apuntadores
    while (counter <= 10)
    {
        printf("\n EL valor del contador es: %d", counter);
        usleep(2000000); //muestra cada 2s
    }
    return NULL;
    //pthread_exit(NULL);
}

int main(){
    counter = 0;
    pthread_t hilo; // Creación del hilo

    pthread_create(&hilo, NULL, muestraContador, NULL);
    for(int i = 0; i < 10; i++){
        printf("\nIncrementando contador: ");
        counter+=1;
        usleep(2000000);
    }
    pthread_join(hilo, NULL);
}