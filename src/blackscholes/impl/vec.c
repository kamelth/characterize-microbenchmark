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

# define inv_sqrt_2xPI 0.39894228040143270286

float32x4_t expq_f32_neon(float32x4_t InputX) {
    float result[4];
    vst1q_f32(result, InputX);
    for (int i = 0; i < 4; i++) {
      result[i] = exp(result[i]); // Scalar exp for each element
    }
    return vld1q_f32(result); // Load the result back into a vector
}

float32x4_t logq_f32_neon(float32x4_t InputX) {
    float result[4];
    vst1q_f32(result, InputX);
    for (int i = 0; i < 4; i++) {
      result[i] = log(result[i]); // Scalar exp for each element
    }
    return vld1q_f32(result); // Load the result back into a vector
}

float32x4_t v_cndf(float32x4_t InputX) {
  // Check for negative value of InputX then set sign 1, otherisw sign is 0;
  int sign_ints[4];
  for (int j = 0; j < 4; ++j) {
    if ( InputX[j] < 0.0) {
      sign_ints[j] = 1;
    } else
      sign_ints[j] = 0;
  }

  int32x4_t sign = vld1q_s32(sign_ints);

  InputX = vabsq_f32(InputX);

  float32x4_t OutputX;
  float32x4_t xInput;
  float32x4_t xNPrimeofX;
  float32x4_t expValues;
  float32x4_t xK2;
  float32x4_t xK2_2, xK2_3;
  float32x4_t xK2_4, xK2_5;
  float32x4_t xLocal, xLocal_1;
  float32x4_t xLocal_2, xLocal_3;

  // Check for negative value of InputX
  xInput = InputX;

  // Compute NPrimeX term common to both four & six decimal accuracy calcs
  expValues = vmulq_f32(vdupq_n_f32(-0.5f), vmulq_f32(InputX, InputX));
  expValues = expq_f32_neon(expValues);
  xNPrimeofX = vmulq_f32(expValues, vdupq_n_f32(inv_sqrt_2xPI));
  xK2 = vmulq_f32(vdupq_n_f32(0.2316419f), xInput);
  xK2 = vaddq_f32(vdupq_n_f32(1.0f), xK2);
  xK2 = vdivq_f32(vdupq_n_f32(1.0f), xK2);
  xK2_2 = vmulq_f32(xK2, xK2);
  xK2_3 = vmulq_f32(xK2_2, xK2);
  xK2_4 = vmulq_f32(xK2_3, xK2);
  xK2_5 = vmulq_f32(xK2_4, xK2);

  xLocal_1 = vmulq_f32(vdupq_n_f32(0.319381530f), xK2);
  xLocal_2 = vmulq_f32(vdupq_n_f32(-0.356563782f), xK2_2);
  xLocal_3 = vmulq_f32(vdupq_n_f32(1.781477937f), xK2_3);
  xLocal_2 = vaddq_f32(xLocal_2, xLocal_3);
  xLocal_3 = vmulq_f32(vdupq_n_f32(-1.821255978f), xK2_4);
  xLocal_2 = vaddq_f32(xLocal_2, xLocal_3);
  xLocal_3 = vmulq_f32(vdupq_n_f32(1.330274429f), xK2_5);
  xLocal_2 = vaddq_f32(xLocal_2, xLocal_3);
  xLocal_1 = vaddq_f32(xLocal_2, xLocal_1);
  xLocal = vmulq_f32(xLocal_1, xNPrimeofX);
  xLocal = vsubq_f32(vdupq_n_f32(1.0f), xLocal);
  OutputX = xLocal;

  float OutputX_scalars[4];
  for (int j = 0; j < 4; ++j) {
    if ( sign[j] ) {
      OutputX_scalars[j] = OutputX[j] = 1.0 - OutputX[j];
    } else {
      OutputX_scalars[j] = OutputX[j];
    }
  }

  OutputX = vld1q_f32(OutputX_scalars);

  return OutputX;
 }

float32x4_t v_blackScholes (float32x4_t sptprice, float32x4_t strike, float32x4_t rate, float32x4_t volatility, float32x4_t otime, int32x4_t otype, float32x4_t timet) {
  float32x4_t OptionPrice ;

  // local private working variables for the calculation
  float32x4_t xStockPrice ;
  float32x4_t xStrikePrice ;
  float32x4_t xRiskFreeRate ;
  float32x4_t xVolatility ;
  float32x4_t xTime ;
  float32x4_t xSqrtTime ;
  float32x4_t logValues ;
  float32x4_t xLogTerm ;
  float32x4_t xD1 ;
  float32x4_t xD2 ;
  float32x4_t xPowerTerm ;
  float32x4_t xDen ;
  float32x4_t d1 ;
  float32x4_t d2 ;
  float32x4_t FutureValueX ;
  float32x4_t NofXd1 ;
  float32x4_t NofXd2 ;
  float32x4_t NegNofXd1 ;
  float32x4_t NegNofXd2 ;

  xStockPrice = sptprice ;
  xStrikePrice = strike ;
  xRiskFreeRate = rate ;
  xVolatility = volatility ;
  xTime = otime ;

  xSqrtTime = vsqrtq_f32(xTime);
  logValues = logq_f32_neon(vdivq_f32(sptprice, strike));
  xLogTerm = logValues;

  xPowerTerm = vmulq_f32(xVolatility, xVolatility);
  xPowerTerm = vmulq_f32(vdupq_n_f32(0.5f), xPowerTerm);

  xD1 = vaddq_f32(xRiskFreeRate, xPowerTerm);
  xD1 = vmulq_f32(xD1, xTime);
  xD1 = vaddq_f32(xD1, xLogTerm);
  xDen = vmulq_f32(xVolatility, xSqrtTime);
  xD1 = vdivq_f32(xD1, xDen);
  xD2 = vsubq_f32(xD1, xDen);


  d1 = xD1 ;
  d2 = xD2 ;

  NofXd1 = v_cndf ( d1 );
  NofXd2 = v_cndf ( d2 );

  FutureValueX = vmulq_f32(strike, expq_f32_neon(vnegq_f32(vmulq_f32(rate, otime))));

  float32x4_t callPrice = vsubq_f32(vmulq_f32(sptprice, NofXd1), vmulq_f32(FutureValueX, NofXd2));

  float32x4_t putPrice = vsubq_f32(vmulq_f32(FutureValueX, vsubq_f32(vdupq_n_f32(1.0f), NofXd2)), vmulq_f32(xStockPrice, vsubq_f32(vdupq_n_f32(1.0f), NofXd1)));

  OptionPrice = vbslq_f32(vceqq_s32(otype, vdupq_n_s32(0)), callPrice, putPrice);

  return OptionPrice;
}

/* Alternative Implementation */
void* impl_vector(void* args)
{
  /* Get the argument struct */
  args_t* parsed_args = (args_t*)args;

  size_t num_stocks = parsed_args->num_stocks;
  float* spotPrices = parsed_args->sptPrice;
  float* strikes = parsed_args->strike;
  float* rates = parsed_args->rate;
  float* volatilities = parsed_args->volatility;
  float* otimes = parsed_args->otime;
  char* otypecs = parsed_args->otype;

  float* results = parsed_args->output;

  for (size_t i = 0; i < num_stocks; i += 4) {
    float32x4_t xStockPrice = vld1q_f32(&spotPrices[i]);
    float32x4_t xStrikePrice = vld1q_f32(&strikes[i]);
    float32x4_t xRate = vld1q_f32(&rates[i]);
    float32x4_t xVolatility = vld1q_f32(&volatilities[i]);
    float32x4_t xTime = vld1q_f32(&otimes[i]);

    int otype_ints[4];
    for (int j = 0; j < 4; ++j) {
      otype_ints[j] = (tolower(otypecs[i + j]) == 'p') ? 1 : 0;
    }

    int32x4_t otypes = vld1q_s32(otype_ints);

    float32x4_t oprice = v_blackScholes(xStockPrice, xStrikePrice, xRate, xVolatility, xTime, otypes, vdupq_n_f32(0.0f));

    for (int j = 0; j < 4; ++j) {
      results[i + j] = oprice[j];
    }


  }

  return NULL;
}