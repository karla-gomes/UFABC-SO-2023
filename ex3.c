#include<stdio.h>   // Standard I/O 
#include<unistd.h>  // Unix Standard 
#include<pthread.h> // POSIX Thread 
#include <stdlib.h> // Randomic NUmbers


int vetor[20]; //Vetor que recebera os valores aleatorios

struct Resultados{ //Struct para armazenar os valores estatisticos
	int max;
	int min;
	float media;
	int moda;
	
}Resultados;

void *minVetor(void *vetor){
	
	int i; 
	int *elements = (int*)vetor; 
	Resultados.min = elements[0]; 

	for(i = 0; i < 20; i++){	
		if(elements[i] < Resultados.min){	
			Resultados.min = elements[i];	
		}
	}
	
	return NULL;
}

void *maxVetor(void *vetor){
	
	int i;	
	int *elements = (int*)vetor; 
		
	for(i = 0; i < 20; i++){	
		if(elements[i] > Resultados.max){	
			Resultados.max = elements[i];
		}
	}
	return NULL;
}

void *mediaVetor(void *vetor){
	
	int i;	
	int *elements = (int*)vetor; 	
	
	for(i = 0; i < 20; i++){		
		Resultados.media += elements[i];		
	}
	
	Resultados.media = Resultados.media/20;	
	
	return NULL;
}

/*
void *modaVetor(void *vetor) {
}
*/

int main()
{
    pthread_t thr[3];   // Matrix of Thread Descriptor
    printf("O processo principal é %d\n", getpid());

    // Carrega Vetor com Valores Randômicos
    for(int i = 0; i < 20; i++) 
    {
    	vetor[i] = rand() % 10 + 1;  // Valores entre 1 e 10
    	printf("%d\n", vetor[i]);
    }


	pthread_create(&thr[0], NULL, minVetor, (void*)vetor);
	pthread_create(&thr[1], NULL, maxVetor, (void*)vetor);
	pthread_create(&thr[2], NULL, mediaVetor, (void*)vetor);
	//pthread_create(&thr[3], NULL, modaVetor, (void*)vetor);
	

    // Suspende a execução da thread CHAMADORA até que as thread CHAMADAS terminem
    (void) pthread_join(thr[0], NULL);
    (void) pthread_join(thr[1], NULL);
    (void) pthread_join(thr[2], NULL);
    //(void) pthread_join(thr[3], NULL);


	/*Prompt the user with our results*/
	printf("Valor minimo: %d\nValor maximo: %d\nMedia: %f\n", Resultados.min, Resultados.max, Resultados.media);

    pthread_exit(NULL);

}
