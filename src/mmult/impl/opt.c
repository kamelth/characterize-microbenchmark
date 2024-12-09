/* opt.c
 *
 * Author: Kamel Gerado
 * Date  : 9  Dec. 2024
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

void* impl_scalar_blocking_opt(void* args)
{
  /* Get the argument struct */
  args_t* parsed_args = (args_t*)args;

  /* Get all the arguments */
  register       float*   R = (      float*)(parsed_args->R);
  register const float*   A = (const float*)(parsed_args->A);
  register const float*   B = (const float*)(parsed_args->B);
  register       int      M =              parsed_args->M;
  register       int      N =              parsed_args->N;
  register       int      P =              parsed_args->P;
  register       int      b =              parsed_args->b;

  /* Initialize the result matrix */
  for (register int i = 0; i < M; i++) {
      for (register int j = 0; j < P; j++) {
          R[j + i * P] = 0;
      }
  }

  /* Perform blocked matrix multiplication */
  for (register int ii = 0; ii < M; ii += b) {
      for (register int jj = 0; jj < P; jj += b) {
          for (register int kk = 0; kk < N; kk += b) {
              for (register int i = ii; i < ii + b && i < M; i++) {
                  for (register int j = jj; j < jj + b && j < P; j++) {
                      float val = R[j + i * P];
                      for (register int k = kk; k < kk + b && k < N; k++) {
                          val += A[k + i * N] * B[j + k * P];
                      }
                      R[j + i * P] = val;
                  }
              }
          }
      }
  }

  /* Done */
  return NULL;
}
