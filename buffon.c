/** @file     buffon.c
 *  @brief    Buffon functions.
 *  @author   Marcelo Pinto (xmrcl0@gmail.com)
 *  @date     09/13/2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include <limits.h>

void
help (void)
{
  printf ("usage: buffon [-h] [-v] -n <ndrop> -l <nsize>\n");
  printf ("Calculates PI using Buffon's technique\n\n");
  printf ("Options:\n");
  printf ("  -n <ndrop>    Number of needle drops\n");
  printf ("  -l <nsize>    Needle size\n");
  printf ("  -v            Verbose mode\n");
  printf ("  -h            Show this help message and exit\n\n");
  printf ("Examples:\n");
  printf ("  buffon -n 1000 -l 1            # Drops 1000 time a needle of size 1\n");
  printf ("  buffon -n 1000 -l 1 -v         # Turn on the verbose mode\n");
}


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


void
print_out (double *pi, double *exp_err)
{
  printf ("pi = %g, exp_err = %g, real_err = %g\n", *pi, *exp_err, fabs (M_PI - *pi));
}
