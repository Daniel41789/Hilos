#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 10
int n=10;
int buffer[BUFFER_SIZE];
int counter=0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//vamos a necesitar trabajar con dos señales
pthread_cond_t cond_prod = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_cons = PTHREAD_COND_INITIALIZER;

void * productor(void * arg){
	for(int i=0;i<n;++i){
		pthread_mutex_lock(&mutex);
		while(counter==BUFFER_SIZE){
			pthread_cond_wait(&cond_prod,&mutex);
		//vamos a esperar cuando el buffer este lleno
		}
		counter++;
		buffer[counter]=i;
		//buffer[counter++]=i;
		printf("\nEl productor produce: %d",buffer[counter]);
		//sleep(1);
		pthread_cond_signal(&cond_cons);
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);
}

void * consumidor(void * arg){
	for(int i=0;i<n;++i){
		pthread_mutex_lock(&mutex);
		while(counter==0){
			//no hay que consumir.. por lo tanto, esperamos
			pthread_cond_wait(&cond_cons,&mutex);
		}
		//counter--;
		//int consumo=buffer[counter];
		int consumo=buffer[counter--];
		printf("\nEl consumidor consume: %d",consumo);
		pthread_cond_signal(&cond_prod);
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);
}

int main(){
	pthread_t hiloProd, hiloCons;
	pthread_create(&hiloProd,NULL,productor,NULL);
	pthread_create(&hiloCons,NULL,consumidor,NULL);
	
	pthread_join(hiloProd,NULL);
	pthread_join(hiloCons,NULL);
}