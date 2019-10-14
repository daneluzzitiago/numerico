#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define SIZE 3
#define IT 20
#define ERROR 0.00000001

typedef struct Matrix{
	long double **data;
	int size;
}Matrix;

typedef struct Vector{
	long double *data;
	int size;
}Vector;


Matrix init_matrix(int size){
	Matrix mat;
	mat.size = size;
	mat.data = (long double**)malloc(sizeof(long double*) * size);
	int i, j;
	for(i = 0; i < size; i++){
		mat.data[i] = (long double*)malloc(sizeof(long double) * size);
	}
	return mat;
}


Vector init_vector(int size){
	Vector vet;
	vet.size = size;
	vet.data = (long double*)malloc(sizeof(long double) * size);
	int i;
	for(i = 0; i < size; i++){
		vet.data[i] = 0;
	}
	return vet;
}


long double rules(int i, int j){
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
			printf("%Lf ", mat.data[i][j]);
		}
		printf("\n");
	}	
}

void print_vector(Vector vec){
	int i;
	for(i = 0; i < vec.size; i ++){
		printf("%Lf\n", vec.data[i]);
	}
	printf("\n");
}

void vetor1(Matrix mat, Vector vet, int size){
	
	int i, j;
	long double somaMatriz[size];

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
	//print_vector(vet);
}

void vetor2(Vector vet, int size){
	int i;

	for(i = 0; i < size; i++){
		vet.data[i] = 1.0/(i + 1);
	}
	//print_vector(vet);
}

int gauss_seidel(Matrix A, Vector x, Vector b, long double error, int itmax){
	Vector x_prox = init_vector(x.size);
	int i, j, k;
	bool conv;
	for(i = 0; i < itmax; i++){
		//DEF X_PROX
		for(j = 0; j < x.size; j++){
			long double soma = 0;
			for(k = j + 1; k < x.size; k++){
				soma += A.data[j][k]*x.data[k];
			}
			long double soma_prox = 0;
			for(k = 0; k < j; k++){
				soma_prox += A.data[j][k]*x_prox.data[k];
			}
			x_prox.data[j] = (1/A.data[j][j])*(b.data[j] - soma - soma_prox);
		}
		//VERIFY X - X_PROX
		for(j = 0; j < x.size; j++){
			conv = true;
			long double value = fabs(x.data[j] - x_prox.data[j]);
			if (value > error){
				conv = false;
			}
			if(conv){
				printf("Convergiu na iteração: %d\n\n", i);
				free(x_prox.data);
				return 1;	
			}
		}
		//UPDATE VECTOR X
		for(j = 0; j < x.size; j++){
			x.data[j] = x_prox.data[j];
		}
	}
	free(x_prox.data);
	printf("METODO GAUSS-SEIDEL DIVERGIU.\n\n");
	return -1;
}

int main(void){
	//Questao a) VER FUNÇÃO gauss_seidel()
	
	//Questao b)	
	Matrix mat_1 = init_matrix(50);
	apply_matrix_rules(mat_1);
	int it_1 = 50*5;
	Vector x_1 = init_vector(50);
	Vector vector_1 = init_vector(50);
	vetor1(mat_1, vector_1, 50);
	gauss_seidel(mat_1, x_1, vector_1, ERROR, it_1);
	
	free(x_1.data);
	free(vector_1.data);
	free_matrix(mat_1);
	
	Matrix mat_2 = init_matrix(100);
	apply_matrix_rules(mat_2);
	int it_2 = 100*5;
	Vector x_2 = init_vector(100);
	Vector vector_2 = init_vector(100);
	vetor1(mat_2, vector_2, 100);
	gauss_seidel(mat_2, x_2, vector_2, ERROR, it_2);
	
	free(x_2.data);
	free(vector_2.data);
	free_matrix(mat_2);
	
	//Questão c)	
	Matrix mat_3 = init_matrix(500);
	apply_matrix_rules(mat_3);
	int it_3 = 500;
	Vector vector_3 = init_vector(500);
	vetor2(vector_3, 500);
	Vector x_3 = init_vector(500);
	gauss_seidel(mat_3, x_3, vector_3, ERROR, it_3);

	free(x_3.data);
	free(vector_3.data);
	free_matrix(mat_3);

	return 0;
}
