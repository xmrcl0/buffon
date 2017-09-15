/** @file     buffon.c
 *  @brief    Calculates pi using Buffon's technique.
 *  @author   Marcelo Pinto (xmrcl0@gmail.com)
 *  @date     09/15/2017
 *  @version  0.8
 */

#include <utils.h>
#include <buffon.h>

int param_parse(int argc, char **argv, unsigned long long *n, double *l, int *sflag, int *vflag)
{
  int i, c, nflag = 0, lflag = 0;

  opterr = 0;
  while ((c = getopt (argc, argv, "l:n:s::v::h::b:")) != -1)
  {
    switch (c)
    {
    case 'n':
      nflag = 1;
      if (!is_integer (optarg))
      {
	      fprintf (stderr, "%s: error: number of drops must be an integer\n", argv[0]);
	      return 1;
      }
      else
	      *n = strtoull (optarg, NULL, 10);
      break;
    case 'l':
      lflag = 1;
      if (!is_positive_number (optarg))
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
	    return 0;
      break;
    case '?':
      fprintf (stderr, "%s: error: invalid option\n", argv[0]);
      fprintf (stderr, "usage: buffon [-h] [-s] [-v] [-b <bzise>] -n <ndrop> -l <nsize>\n");
      return 1;
    default:
      fprintf (stderr, "usage: buffon [-h] [-s] [-v] [-b <bzise>] -n <ndrop> -l <nsize>\n");
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
    fprintf (stderr, "usage: buffon [-h] [-s] [-v] [-b <bzise>] -n <ndrop> -l <nsize>\n");
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
  if (param_parse (argc, argv, &n, &l, &sflag, &vflag))
  {
    exit (EXIT_FAILURE);
  }

  // Buffon experiment
  buffon_exp(l, n, &pi, &exp_err);

  // Print output
  print_out(&pi, &exp_err);

  return 0;
}
