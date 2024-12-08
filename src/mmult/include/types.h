/* types.h
 *
 * Author: Khalid Al-Hawaj
 * Date  : 13 Nov. 2023
 * 
 * This file contains all required types decalartions.
*/

#ifndef __INCLUDE_TYPES_H_
#define __INCLUDE_TYPES_H_

typedef struct {
  int m;
  int n;
  int p;
} args_t;


struct Matrix {
  int m;
  int n;
  int* content;
};

#endif //__INCLUDE_TYPES_H_
