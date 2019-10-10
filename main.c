//This is a test

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int i;
	int k;
	int key;
	struct Node *vertical_next;
	struct Node *horizontal_next;
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

int main(void){
	Matrix mat = init_matrix(12);
	apply_matrix_rules(mat);
	print_matrix(mat);
	free_matrix(mat);
	return 0;
}
