#include <stdio.h>
#include <stdlib.h>

#define SIZE 5


typedef struct Node{
	int i;
	int k;
	int key;
}Node;


typedef struct Matrix{
	Node **data;
	int size;
}Matrix;


Matrix init_matrix(int size){
	printf("\n\nInitializing matrix\n\n");
	Matrix mat;
	mat.size = size;
	mat.data = (Node**)malloc(sizeof(Node*) * size);
	int i, j;
	for(i = 0; i < size; i++){
		mat.data[i] = (Node*)malloc(sizeof(Node) * size);
	}
	return mat;
}

Matrix init_vector(int size){
	Matrix vet;
	vet.size = size;
	vet.data = (Node**)malloc(sizeof(Node*) * size);

	return vet;
}

int rules(int i, int j){
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
			mat.data[i][j].key = rules(i, j);
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
			printf("%2d ", mat.data[i][j].key);
		}
		printf("\n");
	}	
}

void vetorBi(Matrix mat, Matrix vet, int size){
	printf("\n\nInitializing vector bi\n");
	
	int i, j;
	int somaMatriz[size];

	for(i = 0; i < size; i++){
		somaMatriz[i] = 0;
	}
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			somaMatriz[i] = somaMatriz[i] + mat.data[i][j].key;
		}
		vet.data[i] = somaMatriz[i];
		//printf("i: %d // vet: %d\n", i, vet.data[i]);
	}

	printf("vet = [");
	for(i = 0; i < size; i++){
		printf(" %d", vet.data[i]);
	}
	printf("]\n");

}

int main(void){
	Matrix mat = init_matrix(SIZE);
	Matrix vector = init_vector(SIZE);
	apply_matrix_rules(mat);
	print_matrix(mat);

	vetorBi(mat, vector, SIZE);
	


	free_matrix(mat);

	return 0;
}
