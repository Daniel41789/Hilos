#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Inicializar la semilla para la generación de números aleatorios
    srand(time(NULL));

    // Generar un número aleatorio entre 0 y 1
    int random_number = (int)rand() % 2;

    printf("Número aleatorio entre 0 y 1: %d\n", random_number);

    return 0;
}
