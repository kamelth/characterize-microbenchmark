/* naive.c
 *
 * Author:
 * Date  :
 *
 *  Description
 */

/* Standard C includes */
#include <stdlib.h>

/* Include common headers */
#include "common/macros.h"
#include "common/types.h"

/* Include application-specific headers */
#include "include/types.h"

/* Naive Implementation */
#pragma GCC push_options
#pragma GCC optimize ("O1")

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

void* impl_scalar_naive(void* args)
{
  args_t* input_args = (args_t*)args;

  int m = input_args->m;
  int n = input_args->n;
  int p = input_args->p;

  struct Matrix A;
  struct Matrix B;
  A = rand_matrix(&A, m, n);
  B = rand_matrix(&B, n, p);
  struct Matrix R = mmult(A, B);

  // Return NULL as per the thread-safe function convention
  return NULL;
}

#pragma GCC pop_options
