/** @file     buffon.c
 *  @brief    Buffon functions.
 *  @author   Marcelo Pinto (xmrcl0@gmail.com)
 *  @date     09/15/2017
 *  @update   09/21/2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include <limits.h>


int
drop_needle (double needle_size)
{
  double a, b;

  a = (double) rand () / (double) RAND_MAX *M_PI_2;
  b = (double) rand () / (double) RAND_MAX *needle_size;
  if (needle_size / 2 * cos (a) >= b)
    return 1;
  return 0;
}


void
buffon_exp (float l, unsigned long long int n, double *p, double *s)
{
  int i;
  long double n1;

  srand ((unsigned) time (NULL));
  for (i = 1, n1 = 1; i <= n; i++)
  {
    n1 = n1 + drop_needle (l);
    *p = (long double) i / (long double) n1;
    *s = (long double) *p / (long double) sqrt (i);
  }
}
