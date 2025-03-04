/* hemlock-argparser - a generic arguement parser written for HEMLOCK.
 * <https://github.com/SoftFauna/hemlock-argparser.git>
 * Copyright (c) 2025 The SoftFauna Team */


#include "argparser.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static void print_help (FILE *output);

int
main (int argc, char **argv)
{
    const enum
    {
        ARG_INFILE = CONARG_ID_CUSTOM,
        ARG_OUTFILE,
        ARG_VERBOSE,
        ARG_TERSE,
        ARG_HELP,
        ARG_VERSION,
    };

    const conarg_t ARG_LIST[] =
    {
        { ARG_INFILE,  NULL, "infile",  CONARG_PARAM_REQUIRED },
        { ARG_OUTFILE, NULL, "outfile", CONARG_PARAM_REQUIRED },
        { ARG_VERBOSE, "-v", "--verbose", CONARG_PARAM_NONE },
        { ARG_TERSE,   "-t", "--terse",   CONARG_PARAM_NONE },
        { ARG_HELP,    "-h", "--help",    CONARG_PARAM_NONE },
        { ARG_VERSION, "-V", "--version", CONARG_PARAM_NONE },
    };
    const size_t ARG_COUNT = sizeof (ARG_LIST) / sizeof (*ARG_LIST);
    
    conarg_status_t param_stat = CONARG_STATUS_NA;
    int id = 0;

    bool verbose = false;
    char *infile = NULL;
    char *outfile = NULL;

    /* skip executable name */
    CONARG_STEP (argc, argv);

    /* get arguements */
    while (argc > 0)
    {
        /* parse the current *argv */
        id = conarg_check (ARG_LIST, ARG_COUNT, argc, argv, &param_stat);

        /* preform diff actions based on result */
        switch (id)
        {
        case ARG_INFILE:
            CONARG_STEP (argc, argv);
            infile = conarg_get_param (argc, argv);
            break;

        case ARG_OUTFILE:
            CONARG_STEP (argc, argv);
            outfile = conarg_get_param (argc, argv);
            break;

        case ARG_VERBOSE:
            verbose = true;
            break;

        case ARG_TERSE:
            verbose = false;
            break;

        case ARG_HELP:
            print_help (stdout);
            exit (EXIT_SUCCESS);

        case ARG_VERSION:
            (void)fprintf (stdout, "print version page\n");
            exit (EXIT_SUCCESS);

        case CONARG_ID_PARAM_ERROR:
            (void)fprintf (stderr, "error: the '%s' arguement expects a parameter\n", *argv);
            print_help (stderr);
            exit (EXIT_FAILURE);

        case CONARG_ID_UNKNOWN:
            (void)fprintf (stderr, "error: unknown arguement '%s'\n", *argv);
            print_help (stderr);
            exit (EXIT_FAILURE);

        default:
            (void)fprintf (stderr, "error: unknown\n");
            print_help (stderr);
            exit (EXIT_FAILURE);
        } /* switch-case */
        
        /* iterate over argc/argv */
        CONARG_STEP (argc, argv);

    } /* while loop */

    (void)fprintf (stdout, "results:\n");
    (void)fprintf (stdout, "  infile:  '%s'\n", infile);
    (void)fprintf (stdout, "  outfile: '%s'\n", outfile);
    (void)fprintf (stdout, "  verbose: %d\n", verbose);

    exit (EXIT_SUCCESS);
}


static void 
print_help (FILE *output)
{
    fprintf (output, 
        "usage: argparser_ex <options>\n"
        "options:\n"
        "  infile <file>\n"
        "  outfile <file>\n"
        "  -v, --verbose\n"
        "  -t, --terse\n"
        "  -h, --help\n"
        "  -V, --version\n"
    );
}


/* end of file */