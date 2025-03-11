/* hemlock-argparser example - a generic arguement parser written for HEMLOCK.
 * <https://github.com/SoftFauna/hemlock-argparser.git>
 * Copyright (c) 2025 The SoftFauna Team 
 * MIT License */

#include "cli.h"

#include <stdio.h>


int
main (int argc, char **argv)
{
    cli_results_t cli_results = { 0 };

    cli_parser (argc, argv, &cli_results);
    printf ("results\n");
    printf ("  verbosity:   %d\n", cli_results.verbose);
    printf ("  index:       %d\n", cli_results.index);
    printf ("  infile:     '%s'\n", cli_results.infile);
    printf ("  outfile:    '%s'\n", cli_results.outfile);
    printf ("  dest:       '%s'\n", cli_results.dest);
    printf ("  badtype:     %d\n", cli_results.badtype);
    printf ("  reasonable:  %d\n", cli_results.reasonable);
    printf ("  too_long_a:  %d\n", cli_results.too_long_a);
    printf ("  too_long_b:  %d\n", cli_results.too_long_b);

    return 0;
}

/* end of file */
