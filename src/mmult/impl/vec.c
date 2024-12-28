/* vec.c
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

#include <math.h>
#include <ctype.h>
#include <stdio.h>

#include <arm_neon.h>

/* Alternative Implementation */
void* impl_vector(void* args) {
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
          R[j + i * P] = 0.0;
      }
  }

  for (register int ii = 0; ii < M; ii += b) {
      for (register int jj = 0; jj < P; jj += b) {
          for (register int kk = 0; kk < N; kk += b) {
              for (register int i = ii; i < ii + b && i < M; i++) {
                  for (register int j = jj; j < jj + b && j < P; j++) {
                      float32x4_t result_vec = vdupq_n_f32(0.0f);

                      for (register int k = kk; k < kk + b && k + 4 <= N; k += 4) {
                          float32x4_t a_vec = vld1q_f32(&A[k + i * N]);
                          float32x4_t b_vec = vld1q_f32(&B[j + k * P]);

                          result_vec = vmlaq_f32(result_vec, a_vec, b_vec);
                      }

                      float32x2_t sum_pair = vadd_f32(vget_low_f32(result_vec), vget_high_f32(result_vec));
                      float final_sum = vget_lane_f32(vpadd_f32(sum_pair, sum_pair), 0);

                      for (register int k = kk + (N & ~3); k < kk + b && k < N; k++) {
                        final_sum += A[k + i * N] * B[j + k * P];
                      }

                      R[j + i * P] += final_sum;
                  }
              }
          }
      }
  }

  /* Done */
  return NULL;
}
