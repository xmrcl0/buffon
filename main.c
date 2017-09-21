/** @file     main.c
 *  @brief    Calculates pi using Buffon's technique.
 *  @author   Marcelo Pinto (xmrcl0@gmail.com)
 *  @date     09/15/2017
 *  @update   09/21/2017
 */

#include <utils.h>
#include <buffon.h>


void
help (void)
{
  printf ("usage: buffon [-h] [-v] -n <ndrop> -l <nsize>\n");
  printf ("Calculates PI using Buffon's technique\n\n");
  printf ("Options:\n");
  printf ("  -n <ndrop>    Number of needle drops\n");
  printf ("  -l <nsize>    Needle size\n");
  printf ("  -h            Show this help message and exit\n\n");
  printf ("Examples:\n");
  printf ("  buffon -n 1000 -l 1            # Drops 1000 time a needle of size 1\n");
}


int
parse_cmdline(int argc, char **argv, unsigned long long *n, double *l, int *sflag, int *vflag)
{
  int i, c, nflag = 0, lflag = 0;

  opterr = 0;
  while ((c = getopt (argc, argv, "l:n:h::")) != -1)
  {
    switch (c)
    {
    case 'n':
      nflag = 1;
      if (!is_natural_num (optarg))
      {
	      fprintf (stderr, "%s: error: number of drops must be an integer\n", argv[0]);
	      return 1;
      }
      else
	      *n = strtoull (optarg, NULL, 10);
      break;
    case 'l':
      lflag = 1;
      if (!is_positive_num (optarg))
      {
	      fprintf (stderr, "%s: error: needle size must be positive\n", argv[0]);
	      return 1;
      }
      else
	      *l = strtod (optarg, NULL);
      break;
    case 's':
      *sflag = 1;
      break;
    case 'v':
      *vflag = 1;
      break;
    case 'h':
      help ();
	    return 1;
      break;
    case '?':
      fprintf (stderr, "%s: error: invalid option\n", argv[0]);
      fprintf (stderr, "usage: buffon [-h] -n <ndrop> -l <nsize>\n");
      return 1;
    default:
      fprintf (stderr, "usage: buffon [-h] -n <ndrop> -l <nsize>\n");
      return 1;
    }
  }

  // Check integer overflow 
  for (i = optind; i < argc; i++)
  {
    fprintf (stderr, "%s: error: too many or too few arguments\n", argv[0]);
    return 1;
  }

  // Check integer overflow 
  if (n + 1 < n)
  {
    fprintf (stderr, "%s: error: number of drops must be less than %llu \n", argv[0], ULLONG_MAX);
    return 1;
  }

  // Check if obrigatory argumets were given
  if (nflag == 0 || lflag == 0)
  {
    fprintf (stderr, "%s: error: too few parameters\n", argv[0]);
    fprintf (stderr, "usage: buffon [-h] -n <ndrop> -l <nsize>\n");
    return 1;
  }
  return 0;
}


int
main (int argc, char **argv)
{
  int sflag = 0, vflag = 0;
  unsigned long long int n = 0;
  double l = 0, pi, exp_err, r;

  // Parse command line arguments
  if (parse_cmdline (argc, argv, &n, &l, &sflag, &vflag))
  {
    return 1;
  }

  // Buffon experiment
  buffon_exp(l, n, &pi, &exp_err);

  // Print output
  printf ("pi = %g, exp_err = %g, real_err = %g\n", pi, exp_err, fabs (M_PI - pi));

  return 0;
}
