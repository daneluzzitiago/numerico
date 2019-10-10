#include <stdio.h>

typedef struct Node{
	int i;
	int k;
	int key;
	*Node vertical_next;
	*Node horizontal_next;
}Node;

typedef struct Matrix{
	**Node data;
}Matrix;

int main(void){
	printf("Hello world\n");

	return 0;
}
