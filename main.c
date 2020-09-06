#include <stdio.h>
#include <stdlib.h>

#define NO_OF_COLORS 8
#define COLORS (const char*[NO_OF_COLORS]){"yellow", "blue", "green", "purple", "white", "black", "red", "gray"}

void printMatrix (int**, int);
int isOk (int**, int, int);
void scrollRight (int**, int, int);
int solveMatrix (int**, int, int);

int main(int argc, char *argv[]) {
	int N, i, j;
	int** matrix;
	
	N = 0;
	printf("Please enter a value for N that would dedicate the size of the NxN matrix.\n");
	while (N<3 || N>8){
		printf("N needs to be greater than 2 and less than 9.\n");
		scanf("%d", &N);
	}
	matrix = (int**) malloc (N * sizeof(int*));
	for (i=0;i<N;i++){
		matrix[i] = (int*) malloc (N * sizeof(int));
	}
	
	printf("\nNumbers and the colors they represent:\n");
	for (i=0;i<NO_OF_COLORS;i++){
		printf("%d. %s\n", i, COLORS[i]);
	}
	
	printf("\nPlease enter the numbers/colors for each cell respectively.\n");
	for (i=0;i<N;i++){
		for (j=0;j<N;j++){
			printf("%d x %d: ", i, j);
			scanf("%d", &matrix[i][j]);
			while (matrix[i][j] < 0 || matrix[i][j] > 7){
				printf("Value can not be less than 0 or greater than 7.\n");
				printf("%d x %d: ", i, j);
				scanf("%d", &matrix[i][j]);
			}
		}
	}
	printf("\nGenerated matrix:\n");
	printMatrix(matrix, N);
	printf("Checking the matrix and correcting if neccessary...\n");
		
	if (solveMatrix(matrix, N, 0) == 0){
		printf("This matrix can not be fixed.\n");
	} else {
		printf("Matrix successfully fixed.\n");
		printMatrix(matrix, N);
	}
	return 0;
}

// Function to print the matrix.
void printMatrix (int** matrix, int N){
	int i, j;
	printf("\n");
	for (i=0;i<N;i++){
		for (j=0;j<N;j++){
			printf(" %d ", matrix[i][j]);
		}
		printf("\n\n");
	}
}

// Function to check if the given row is OK compared to the ones above it.
int isOk (int** matrix, int N, int line){
	int i, j, ok;
	ok = 1;
	for (i=0;i<N && ok == 1;i++){
		j = line - 1;
		while (j >= 0 && ok == 1){
			if (matrix[line][i] != matrix[j][i]){
				j--;
			} else {
				//printf("%d x %d ve %d x %d.\n", line, i, j, i);
				ok = 0;
			}
		}
	}
	return ok;
}

// Function to right-shift the given line of the matrix.
void scrollRight (int** matrix, int N, int line){
	int i, tmp;
	tmp = matrix[line][N-1];
	i = N-1;
	while (i > 0){
		matrix[line][i] = matrix[line][i-1];
		i--;
	}
	matrix[line][0] = tmp;
}

// Function to solve the whole matrix.
int solveMatrix (int** matrix, int N, int line){
	int noOfScrolls = 0;
	
	if (line >= N){
		return 1;
	}
		
	while (noOfScrolls < N){
		if (isOk(matrix, N, line) == 1){
			if (solveMatrix(matrix, N, line+1) == 1){
				return 1;
			}
		}
		scrollRight(matrix, N, line);
		noOfScrolls++;
	}
	return 0;
}
