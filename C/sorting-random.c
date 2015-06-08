#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define N_FUNCS 3
#define N_EXEC 20

#define meta_func(func, times, lenght, i) \
	copy_vector(shadow, vector, lenght); \
	t = clock(); \
	func(shadow, 0, lenght); \
	t = clock() - t; \
	printf("[%s]time to sort(%li): %4.10fs\n", #func, lenght, ((double)t/CLOCKS_PER_SEC)); \
	times[i] = ((double)t/CLOCKS_PER_SEC);  

void swap_values(long unsigned *v1, long unsigned *v2){
	int aux;
	aux = *v1;
	*v1 = *v2;
	*v2 = aux;
}

int exist_in_vector(long unsigned *vector, int limit, int num){
	int i;
	for(i = 0; i < limit; i++)
		if (vector[i] == num)
			return true;
	return false;
}


void random_vector(long unsigned *vector, int lenght){
	//alocando campo de variação
	time_t t;
	srand((unsigned) time(&t));

	//atribuindo valores aleatórios entre 0 a 9 no vector de tamanho n
	int i = 0;

	for(i = 0; i < lenght; i++)
		vector[i] = i;

	//shuffle
	i = 0;
	while(i < lenght){
		//indices aleatorios
		register long unsigned ind1 = rand() % lenght, ind2 = rand() % lenght;
		swap_values(vector + ind1, vector + ind2);
		i++;
	}
}


void print_vector(unsigned long *vector, int lenght){ 
	int i;

	printf("\nVetor de tamanho %d: \n\n", lenght);
	for(i = 0; i < lenght; i++){
		printf("n[%d] = %li\n", i, vector[i]);
	}
}

//impelementação mais eficiente, com ordenação usando menos processamento
void bubble_sort(long unsigned *vector, int useless, int lenght){
	register int i, j;
	for(i = 1; i < lenght; i++)
		for(j = lenght - 1; j>= i; j--)
			if(vector[j - 1] > vector[j])
				swap_values(&vector[j - 1], &vector[j]);
}


//métodos de ordenação
//implementação minha do bubble, muito ruim (lenta demais)
void bubble_dumb(long unsigned *vector, int lenght){
	register int sorted, i;

	do{
		sorted = true;
		for(i = 0; i < lenght - 1; i++){
			if(vector[i] > vector[i + 1]){
				swap_values(vector + i, vector + (i + 1));
				sorted = false;
			}
		}
	}while(sorted == false);
}

void merge(long unsigned *A, int e, int q, int d){ 
	long unsigned *temp;
	int p1, p2, tamanho, i, j, k; 
	int fim1 = 0, fim2 = 0; 

	tamanho = d-e+1; 
	p1 = e;                    // Ponteiro do vetor 1 // 
	p2 = q+1;                // Ponteiro do vetor 2 // 
	if ((temp = (long unsigned *) malloc(tamanho*sizeof(long))) != NULL){ 
		 for(i=0; i<tamanho; i++){ 
				if(!fim1 && !fim2){   // Nenhum dos vetores chegou ao fim // 
					if(A[p1] < A[p2]) temp[i]= A[p1++];     // Seleciona o menor // 
					else temp[i] = A[p2++]; // ++p 
					if(p1 > q) fim1 = 1;
					if(p2 > d) fim2 = 1; 
				} 
				else { 
					 if(!fim1)     temp[i]=A[p1++]; 
					 else     temp[i]=A[p2++]; 
				} 
		 } 
		 for(j=0, k=e; j<tamanho; j++, k++)     // Copia do vetor temporário p/ o vetor a ser retornado // 
				 A[k]=temp[j]; 
	} 
	free(temp); 
}


void merge_sort(long unsigned *A, int e, int d){ 
	int q; 
	if (e < d){ 
		q = floor((e+d)/2);     // Determina a metade do vetor // 
		merge_sort(A,e,q);         // Primeira metade // 
		merge_sort(A,q+1,d);     // Segunda metade // 
		merge(A,e,q,d);             // Combina as metades já ordenadas // 
	} 
}


void quick_sort(long unsigned *item, int left, int right){
	int i, j, x, y;
	i = left;
	j = right;
	x = item [ (left+right)/2 ]; /* elemento pivo */ 
	/* particao das listas */
	do{
		/* procura elementos maiores que o pivo na primeira parte*/ 
		while (item[i] < x && i < right) i++; 
		/* procura elementos menores que o pivo na segunda parte */
		while (x < item[j] && j > left)j--;
		if (i <= j){
			/* processo de troca (ordenacao) */
			y = item[i];
			item[i] = item[j];
			item[j] = y;
			i++;
			j--;
		}
	} while(i<=j); 

	/* chamada recursiva */
	if( left<j )
		quick_sort(item, left, j);
	if( i<right )
		quick_sort(item, i, right);
}


// a implementar
void personal_sort(unsigned long *vector, unsigned long lenght){


}

void write_file(double *data, unsigned long lenght){
	FILE *f;

	f = fopen("data.db", "a");

	int i;
	fprintf(f, "%li = ", lenght);
	for(i = 0; i < N_FUNCS; i++)
		fprintf(f, "%d:%.10f | ", i + 1, data[i]);
	fprintf(f, "\n");
	fclose(f);
}

void clear_file(const char* name){
	FILE *p;
	p = fopen(name, "w");
	fclose(p);
}

void copy_vector(long unsigned *destination, long unsigned *source, long unsigned limit){
	int i;
	for(i = 0; i < limit; i++)
		destination[i] = source[i];
}

void sort_methods(long unsigned *vector, double times[N_FUNCS], int tests, long unsigned lenght){
	long unsigned *shadow = NULL;
	clock_t t;
	
	shadow = (long unsigned *) calloc(lenght, sizeof(long));

	//bubble
	meta_func(bubble_sort, times, lenght, 0);
	//merge
	meta_func(merge_sort, times, lenght, 1);
	//quick
	meta_func(quick_sort, times, lenght, 2);

	free(shadow);
}

void media_vector(double (*input)[N_FUNCS], double *output){
	double media = 0.0;
	int i, j;

	for (j = 0; j < N_FUNCS; j++){
		media = 0.0;
		for(i = 0; i < N_EXEC; i++)
			media += input[i][j];
		media /= N_EXEC;
		output[j] = media;
	}
}		


int main(void){
	long unsigned *vector = NULL, lenght;
	int i, j, tests = 0;

	clear_file("data.db");
	printf("Ordenação de números aleatórios distintos\n");
	for(i = 1; i <= 7; i++){
		//alocar
		lenght = pow(10, i);
		vector = (long unsigned*) realloc(vector, lenght*sizeof(long));
		
		if (vector == NULL){
			printf("Não foi possível alocar memória para tamanho n = %li elementos\n", lenght);
			exit(EXIT_FAILURE);
		}

		//gerar vetor aleatorio
		clock_t t; 
		t = clock();
		random_vector(vector, lenght);
		t = clock() - t;
		printf("[random]time to generate (%li): %.10fs\n", lenght, (double)t/CLOCKS_PER_SEC);
		
		double temp_times[N_FUNCS];
		for(j = 0; j < N_EXEC; j++){
			//metodos de ordenação
			sort_methods(vector, temp_times, j, lenght);
			write_file(temp_times, lenght);
		}	
	}

	return EXIT_SUCCESS;
}	