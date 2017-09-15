/** @file     buffon.h
 *  @brief    Function prototypes for buffon.
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

/** @brief Print command help.
 *
 *  @param  void
 *  @return void 
 */
void help (void);

/** @brief Drop needle.
 *
 *  @param[in] n Needle size
 *  @return bool
 */
int drop_needle (double needle_size);

/** @brief Buffon experiment.
 *
 *  @param[in] l  Needle size
 *  @param[in] n  Number of iterations
 *  @param[in] p  Pi value
 *  @param[in] s  Experimental error
 *  @return void 
 */
void buffon_exp (float l, unsigned long long int n, double *p, double *s);

/** @brief Print output.
 *
 *  @param[in] p  Pi value
 *  @param[in] s  Experimental error
 *  @return void 
 */
void print_out (double *pi, double *s);
