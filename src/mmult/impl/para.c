/* para.c
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

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct {
    const float* A;
    const float* B;
    float* R;
    int M, N, P, b;
    int ii_start, ii_end;
    int jj_start, jj_end;
} thread_args_t;


void* compute_blocked_matrix_multiplication(void* args) {
    thread_args_t* t_args = (thread_args_t*)args;

    const float* A = t_args->A;
    const float* B = t_args->B;
    float* R = t_args->R;
    int M = t_args->M;
    int N = t_args->N;
    int P = t_args->P;
    int b = t_args->b;
    int ii_start = t_args->ii_start;
    int ii_end = t_args->ii_end;
    int jj_start = t_args->jj_start;
    int jj_end = t_args->jj_end;

    for (int i = ii_start; i < ii_end; i++) {
        for (int j = jj_start; j < jj_end; j++) {
            R[j + i * P] = 0;
        }
    }

    for (int ii = ii_start; ii < ii_end; ii += b) {
        for (int jj = jj_start; jj < jj_end; jj += b) {
            for (int kk = 0; kk < N; kk += b) {
                for (int i = ii; i < ii + b && i < M; i++) {
                    for (int j = jj; j < jj + b && j < P; j++) {
                        float val = R[j + i * P];
                        for (int k = kk; k < kk + b && k < N; k++) {
                            val += A[k + i * N] * B[j + k * P];
                        }
                        R[j + i * P] = val;
                    }
                }
            }
        }
    }

    return NULL;
}

/* Alternative Implementation */
void* impl_parallel(void* args)
{
  args_t* parsed_args = (args_t*)args;

  // Unpack arguments
  float* R = parsed_args->R;
  const float* A = parsed_args->A;
  const float* B = parsed_args->B;
  int M = parsed_args->M;
  int N = parsed_args->N;
  int P = parsed_args->P;
  int b = parsed_args->b;
  int num_threads = parsed_args->nthreads;

  pthread_t threads[num_threads];
  thread_args_t t_args[num_threads];

  int block_rows_per_thread = (M + num_threads - 1) / num_threads; // Rows per thread
  int block_cols_per_thread = (P + num_threads - 1) / num_threads; // Columns per thread

  for (int t = 0; t < num_threads; t++) {
      t_args[t].A = A;
      t_args[t].B = B;
      t_args[t].R = R;
      t_args[t].M = M;
      t_args[t].N = N;
      t_args[t].P = P;
      t_args[t].b = b;

      t_args[t].ii_start = t * block_rows_per_thread;
      t_args[t].ii_end = (t_args[t].ii_start + block_rows_per_thread > M) ? M : t_args[t].ii_start + block_rows_per_thread;

      t_args[t].jj_start = t * block_cols_per_thread;
      t_args[t].jj_end = (t_args[t].jj_start + block_cols_per_thread > P) ? P : t_args[t].jj_start + block_cols_per_thread;

      pthread_create(&threads[t], NULL, compute_blocked_matrix_multiplication, &t_args[t]);
  }

  // Join threads
  for (int t = 0; t < num_threads; t++) {
    pthread_join(threads[t], NULL);
  }

  return NULL;
}
