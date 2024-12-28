/* scalar.h
 *
 * Author: Khalid Al-Hawaj
 * Date  : 13 Nov. 2023
 *
 * Header for the scalar function.
 */

#ifndef __IMPL_SCALAR_H_
#define __IMPL_SCALAR_H_

/* Function declaration */
void* impl_scalar(void* args);

#endif //__IMPL_SCALAR_H_

#ifndef __BLACKSCHOLES_H_
#define __BLACKSCHOLES_H_

// Declare the functions
float CNDF(float x);
float blackScholes(float sptprice, float strike, float rate, float volatility, float otime, int otype, float timet);

#endif // __BLACKSCHOLES_H_
