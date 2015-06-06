#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
int exist_in_vector(int *vector, int limit, int num){
	int i;
	for(i = 0; i < limit; i++){
		if (vector[i] == num){
			return 1;
		}
	}
	return 0;
}

void random_vector(int *vector, int lenght){
	//alocando campo de variação
	time_t t;
	srand((unsigned) time(&t));

	//atribuindo valores aleatórios entre 0 a 9 no vector de tamanho n
	int i = 0;

	while(i < lenght){
		register int random_num = rand() % lenght;
		//verificar se já existe o número
		if(exist_in_vector(vector, i, random_num))
			continue;
		vector[i] = random_num;
		i++;
	}
}

void print_vector(int *vector, int lenght){ 
	int i;
	
	printf("\nVetor de tamanho %d: \n\n", lenght);
	for(i = 0; i < lenght; i++){
		printf("n[%d] = %d\n", i, vector[i]);
	}
}

int main(){
	int *vector, lenght, i;
	clock_t t;

	printf("Números aleatórios distintos\n");
	for(i = 1; i <= 7; i++){
		lenght = pow(10, i);
		vector = (int *) malloc(lenght*sizeof(int));
		t = clock();
		random_vector(vector, lenght);
		t = clock() -t;
		printf("Tempo para gerar vetor distinto e aleatório de tamanho %d: %4.6fs\n", lenght, ((float)t/CLOCKS_PER_SEC));
		//print_vector(vector, lenght);
		vector = NULL;
	}

	return 0;
}