/**
  EP-1 AGA511
  buffon.c
  Purpose: Calculates pi using Buffon's technique.

  @author: Marcelo Pinto
  @email: mpinto@usp.br
  @version: 0.5
  @date: 8/30/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include <limits.h>
#include <regex.h>



/**
  Verify if a string is a valid integer.

  @param number
  @return bool 
*/
int
is_integer(char *number)
{
  int r;
  regex_t regex;
  const char *pattern = "^[0-9]+$";

  r = regcomp (&regex, pattern, REG_EXTENDED);
  if (r) {
    fprintf(stderr, "Could not compile regex\n");
    exit(1);
  }

  r = regexec (&regex, number, 0, NULL, 0); 
  if (!r) {
    return 1;
  }
  return 0;
}


/**
  Verify if a string is a valid number.

  @param number
  @return bool 
*/
int
is_positive_number(char *number)
{
  int r;
  regex_t regex;
  const char *pattern = "^[0-9]+\\.?([0-9]+)?$";

  r = regcomp (&regex, pattern, REG_EXTENDED);
  if (r) {
    fprintf(stderr, "Could not compile regex\n");
    exit(1);
  }

  r = regexec (&regex, number, 0, NULL, 0); 
  if (!r) {
    return 1;
  }
  return 0;
}


/**
  Print command help.

  @param void
  @return void 
*/
void
help(void)
{
  printf ("usage: buffon [-h] [-s] [-v] [-b <bzise>] -n <ndrop> -l <nsize>\n\n");
  printf ("Calculates PI using Buffon's technique\n\n");
  printf ("Options:\n");
  printf ("  -n <ndrop>    Number of needle drops\n");
  printf ("  -l <nsize>    Needle size\n");
  printf ("  -b <bsize>    Block size to print (verbose mode)\n");
  printf ("  -v            Verbose mode\n");
  printf ("  -s            Show output in csv format\n");
  printf ("  -h            Show this help message and exit\n\n");
  printf ("Exemples:\n");
  printf ("  buffon -n 1000 -l 1            # Drops 1000 time a needle of size 1\n");
  printf ("  buffon -n 1000 -l 1 -v         # Turn on the verbose mode\n");
  printf ("  buffon -n 1000 -l 1 -v -s      # Verbose output in csv format\n");
  printf ("  buffon -n 1000 -l 1 -v -b 100  # Verbose Output in chunks of 100 (default=1)\n");
}


/**
  Buffon experiment

  @param needle size
  @return bool 
*/
int
drop_needle (double needle_size)
{
  double a, b;

  a = (double) rand () / (double) RAND_MAX * M_PI_2;
  b = (double) rand () / (double) RAND_MAX * needle_size;
  if (needle_size / 2 * cos (a) >= b)
    return 1;
  return 0;
}


int
main (int argc, char **argv)
{
  int index, c, block_size = 1;
  int sflag = 0, nflag = 0, vflag = 0, lflag = 0;
  long double r, l, sigma_err, real_err;
  unsigned long long int i, n, n1;

  /* Read and parse command line arguments */
  opterr = 0;
  while ((c = getopt (argc, argv, "l:n:s::v::h::b:")) != -1)
    switch (c)
      {
      case 'n':
        nflag = 1;
        if (!is_integer(optarg)) {
	        fprintf (stderr, "%s: error: number of drops must be an integer\n", argv[0]);
          exit(1);
        }
        else
          n = strtoull(optarg, NULL, 10);
	      break;
      case 'l':
        lflag = 1;
        if (!is_positive_number(optarg)) {
	        fprintf (stderr, "%s: error: needle size must be positive\n", argv[0]);
          exit(1);
        }
        else
          l = strtod(optarg, NULL);
	      break;
      case 's':
	      sflag = 1;
	      break;
      case 'b':
        if (!is_integer(optarg)) {
	        fprintf (stderr, "%s: error: block size must be an integer\n", argv[0]);
          exit(1);
        }
        else
          block_size = atoi(optarg);
        break;
      case 'v':
	      vflag = 1;
	      break;
      case 'h':
        help();
        exit(0);
	      break;
      case '?':
	      fprintf (stderr, "%s: error: invalid option\n", argv[0]);
	      return 1;
      default:
        fprintf (stderr, "usage: buffon [-h] [-s] [-v] [-b <bzise>] -n <ndrop> -l <nsize>\n");
	    abort ();
      }

  for (index = optind; index < argc; index++)
    {
	    fprintf (stderr, "%s: error: too many or too few arguments\n", argv[0]);
      exit (1);
    }

  /* Verify integer overflow */
  if (n + 1 < n)
    {
      fprintf (stderr, "%s: error: number of drops must be less than %llu \n", argv[0], ULLONG_MAX);
      exit (1);
    }

  /* Check if obrigatory argumets were given*/
  if (nflag == 0 || lflag == 0)
    {
      fprintf (stderr, "%s: error: too few parameters\n", argv[0]);
      fprintf (stderr, "usage: buffon [-h] [-s] [-v] [-b <bzise>] -n <ndrop> -l <nsize>\n");
      exit (1);
    }

  /* Buffon experiment */
  srand ((unsigned) time (NULL));
  for (i = 1, n1 = 1; i <= n; i++)
    {
      n1 = n1 + drop_needle (l);

      if (vflag == 1)
	      if (i % block_size == 0)
	      {
	        r = (long double) i / (long double) n1;
	        sigma_err = (long double) r / (long double) sqrt (i);
	        real_err = fabs (M_PI - r);
          
          if (sflag == 1)
	          printf ("%llu, %llu, %.9Lf, %.9Lf, %.9Lf\n", i, n1, r, sigma_err, real_err);
          else
	          printf ("n = %llu, n1 = %llu, pi = %.9Lf, sigma_err = %.9Lf, real_err = %.9Lf\n", i, n1, r, sigma_err, real_err);
	      }
    }

	r = (long double) i / (long double) n1;
	sigma_err = (long double) r / (long double) sqrt (i);
	real_err = fabs (M_PI - r);

  /* Print output */
  if (vflag == 0)
    if (sflag == 1)
	    printf ("%llu, %llu, %.9Lf, %.9Lf, %.9Lf\n", n, n1, r, sigma_err, real_err);
    else
	    printf ("n = %llu, n1 = %llu, pi = %.9Lf, sigma_err = %.9Lf, real_err = %.9Lf\n", n, n1, r, sigma_err, real_err);
  return 0;
}
