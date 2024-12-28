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
#include "scalar.h"

/* Include application-specific headers */
#include "include/types.h"

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct {
  size_t start;
  size_t end;
  float* spotPrices;
  float* strikes;
  float* rates;
  float* volatilities;
  float* otimes;
  char* otypes;
  float* results;
} thread_args_t;


void* compute_black_scholes(void* args) {
  thread_args_t* t_args = (thread_args_t*)args;

  for (size_t i = t_args->start; i < t_args->end; i++) {
    float spotprice = t_args->spotPrices[i];
    float strike = t_args->strikes[i];
    float rate = t_args->rates[i];
    float volatility = t_args->volatilities[i];
    float otime = t_args->otimes[i];
    char otype_c = t_args->otypes[i];
    int otype = (tolower(otype_c) == 'p') ? 1 : 0;

    float oprice = blackScholes(spotprice, strike, rate, volatility, otime, otype, 0);

    t_args->results[i] = oprice;
  }

  return NULL;
}

/* Alternative Implementation */
void* impl_parallel(void* args)
{
  /* Get the argument struct */
  args_t* parsed_args = (args_t*)args;

  int    num_threads = parsed_args->nthreads;
  size_t num_stocks = parsed_args->num_stocks;
  float* spotPrices = parsed_args->sptPrice;
  float* strikes = parsed_args->strike;
  float* rates = parsed_args->rate;
  float* volatilities = parsed_args->volatility;
  float* otimes = parsed_args->otime;
  char* otypes = parsed_args->otype;
  float* results = parsed_args->output;

  pthread_t threads[num_threads];
  thread_args_t t_args[num_threads];

  size_t chunk_size = (num_stocks + num_threads - 1) / num_threads;

  for (size_t t = 0; t < num_threads; t++) {
    size_t start = t * chunk_size;
    size_t end = (start + chunk_size < num_stocks) ? start + chunk_size : num_stocks;

    t_args[t].start = start;
    t_args[t].end = end;
    t_args[t].spotPrices = spotPrices;
    t_args[t].strikes = strikes;
    t_args[t].rates = rates;
    t_args[t].volatilities = volatilities;
    t_args[t].otimes = otimes;
    t_args[t].otypes = otypes;
    t_args[t].results = results;

    pthread_create(&threads[t], NULL, compute_black_scholes, &t_args[t]);
  }

  for (size_t t = 0; t < num_threads; t++) {
    pthread_join(threads[t], NULL);
  }

  return NULL;
}
