#include <stdio.h>
#include <stdlib.h>

#define SIZE 5


typedef struct Matrix{
	double **data;
	int size;
}Matrix;

typedef struct Vector{
	double *data;
	int size;
}Vector;


Matrix init_matrix(int size){
	Matrix mat;
	mat.size = size;
	mat.data = (double**)malloc(sizeof(double*) * size);
	int i, j;
	for(i = 0; i < size; i++){
		mat.data[i] = (double*)malloc(sizeof(double) * size);
	}
	return mat;
}


Vector init_vector(int size){
	Vector vet;
	vet.size = size;
	vet.data = (double*)malloc(sizeof(double) * size);
	return vet;
}


double rules(int i, int j){
	if(i == j){
		return 5;
	}
	if(j-1 >= 0 && i == j-1){
		return -1;
	}
	if(i-1 >= 0 && i-1 == j){
		return -1;
	}
	if(j-3 >= 0 && i == j-3){
		return -1;
	}
	if(i-3 >= 0 && i-3 == j){
		return -1;
	}
	return 0;
}


void apply_matrix_rules(Matrix mat){
	int i, j;
	for(i = 0; i < mat.size; i++){
		for(j = 0; j < mat.size; j++){
			mat.data[i][j] = rules(i, j);
		}
	}
}

void free_matrix(Matrix mat){
	int i;
	for(i = 0; i < mat.size; i++){
		free(mat.data[i]);
	}
	free(mat.data);
}

void print_matrix(Matrix mat){
	int i, j;
	for(i = 0; i < mat.size; i++){
		for(j = 0; j < mat.size; j++){
			printf("%2f ", mat.data[i][j]);
		}
		printf("\n");
	}	
}

void print_vector(Vector vec){
	int i;
	for(i = 0; i < vec.size; i ++){
		printf("%2f ", vec.data[i]);
	}
}

void vetor1(Matrix mat, Vector vet, int size){
	
	int i, j;
	double somaMatriz[size];

	for(i = 0; i < size; i++){
		somaMatriz[i] = 0;
	}
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			somaMatriz[i] = somaMatriz[i] + mat.data[i][j];
		}
		vet.data[i] = somaMatriz[i];
		//printf("i: %d // vet: %d\n", i, vet.data[i]);
	}
	print_vector(vet);
}

void vetor2(Vector vet, int size){
	int i;

	for(i = 0; i < size; i++){
		vet.data[i] = 1.0/(i + 1);
	}
	print_vector(vet);
}

int main(void){
	printf("Creating matrix A...\n");
	Matrix mat = init_matrix(SIZE);
	apply_matrix_rules(mat);
	print_matrix(mat);

	printf("\nCreating vector 1\n"); 	
	Vector vector = init_vector(SIZE);
	vetor1(mat, vector, SIZE);
	

	printf("\nCreating vector 2\n");
	Vector vector2 = init_vector(SIZE);
	vetor2(vector2, SIZE);
	


	free_matrix(mat);

	return 0;
}
