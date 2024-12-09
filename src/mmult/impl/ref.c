/* ref.c
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

/* Reference Implementation */
void* impl_ref(void* args)
{
  /* Get the argument struct */
  args_t* parsed_args = (args_t*)args;

  /* Get all the arguments */
  register       float*   R = (      float*)(parsed_args->R);
  register const float*   A = (const float*)(parsed_args->A);
  register const float*   B = (const float*)(parsed_args->B);
  register       int      M =                parsed_args->M;
  register       int      N =                parsed_args->N;
  register       int      P =                parsed_args->P;

  for (register int i = 0; i < M; i++) {
    for (register int j = 0; j < P; j++) {
        R[j + i * P] = 0;
        for (register int k = 0; k < N; k++) {
          R[j + i * P] += A[k + i * N] * B[j + k * P];
        }
    }
  }

  /* Done */
  return NULL;
}
