#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int main(int argc, char * argv[]){
	int N=atoi(argv[1]);
	float *A, *B, *C;
	srand(time(NULL));
	A=(float*)malloc(sizeof(float)*N);
	B=(float*)malloc(sizeof(float)*N);
	C=(float*)malloc(sizeof(float)*N);
	clock_t inicio, final;

	for(int i=0;i<N;++i){
		A[i]=(float) rand()/RAND_MAX;
		B[i]=(float) rand()/RAND_MAX;
	}
	printf("\nComenzaré a sumar =D");
	inicio=clock();
	for(int i=0;i<N;++i)
		C[i]=A[i]+B[i];
	
	final=clock();
	double tiempo_total=(double)(final-inicio)/CLOCKS_PER_SEC;
	printf("\nEl tiempo de procesamiento es: %f",tiempo_total);
	free(A);
	free(B);
	free(C);
	return 0;
}