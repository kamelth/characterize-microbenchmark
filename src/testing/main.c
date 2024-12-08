#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

struct Matrix {
  int m;
  int n;
  int* content;
};

struct Matrix rand_matrix(struct Matrix *matrix, int m, int n){
  matrix -> m = m;
  matrix -> n = n;
  matrix -> content = (int*)malloc(m * n * sizeof(int));

  for (int i = 0; i < m * n; i++) {
    matrix -> content[i] = rand() % 10;
  };

  return *matrix;
}

struct Matrix mmult(struct Matrix A, struct Matrix B){
  int m   = A.m;
  int n   = A.n;
  int p   = B.n;

  struct Matrix R;
  R.m = m;
  R.n = p;
  R.content = (int*) malloc(m * p * sizeof(int));


  int i, j, k;

  for (i = 0; i < m; i++) {
      for (j = 0; j < p; j++) {
        R.content[j + i * p] = 0;
        for (k = 0; k < n; k++) {
          R.content[j + i * p] += A.content[k + i * n] * B.content[j + k * p];
        }
      }
  }
  return R;
}

int main() {
  srand(20);

  int m = 2;
  int p = 3;
  int n = 2;

  struct Matrix A;
  struct Matrix B;
  A = rand_matrix(&A, m, n);
  B = rand_matrix(&B, n, p);
  struct Matrix R = mmult(A, B);


  // Print the elements of the array 
  printf("["); 
  for (int i = 0; i < m * n; i++) {
    printf("%d, ", A.content[i]);
  }
  printf("]\n"); 

  printf("["); 
  for (int i = 0; i < n * p; i++) {
    printf("%d, ", B.content[i]);
  }
  printf("]\n"); 

  printf("["); 
  for (int i = 0; i < m * p; i++) {
    printf("%d, ", R.content[i]);
  }
  printf("]\n"); 

  // for (int i = 0; i < M * N; i++) printf("[%d] = %d", i, B.content[i]);

  // for (int i = 0; i < M * N; i++) printf("[%d] = %d\n", i, B.content[i]);


  printf("\n"); 

  // printf("The elements of the array R are: "); 
  // for (int i = 0; i < M * N; i++) { 
  //     printf("%d, ", R.content[i]); 
  // } 
  // printf("\n"); 

  // *mat = 5;
  // *(mat + 1) = 6;
  // printf("%d\n", *(mat+1));
  // struct matrix A = {2, 2, {5, 10, 3, 10}};

  // struct matrix B = {2, 2, {7, 6, 7, 4}};
  // for (int i = 0; i < R.M * R.N; i++) printf("[%d] = %d\n", i, A.matrix[i]);

  // struct matrix R = mmult(A, B);


  // for (int i = 0; i < R.M * R.N; i++) printf("[%d] = %d\n", i, R.matrix[i]);
  return 0;
}

// TODO:
// Start to implement direclty on the template
// how can you use the pass args
// 


// data type:
// int a = 10;
// double b = 5.53; // 8 byte == 64 bits
// float c = 4.43; // 4 byte == 32 bits
// char d = "a";
// char e[] = "Kamel Gerado" // string
// int f[3] = [1, 2, 3]
// bool g = false; // need to use #include <stdbool.h>
