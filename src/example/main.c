/* hemlock-argparser - a generic arguement parser written for HEMLOCK.
 * <https://github.com/SoftFauna/hemlock-argparser.git>
 * Copyright (c) 2025 The SoftFauna Team */


#include "argparser.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static void log_usage (FILE *output, copt_t *opts, size_t opt_cnt);
static void log_version (FILE *output);

static int usage_cb (copt_t *opts, size_t opt_cnt, void *data);
static int version_cb (copt_t *opts, size_t opt_cnt, void *data);

static int 
usage_cb (copt_t *opts, size_t opt_cnt, void *data)
{
    log_usage (stdout, opts, opt_cnt);
    exit (EXIT_SUCCESS);
}


static int 
version_cb (copt_t *opts, size_t opt_cnt, void *data)
{
    log_version (stdout);
    exit (EXIT_SUCCESS);
}

int
main (int argc, char **argv)
{
    char *infile = "default infile";
    char *outfile = "default outfile";
    char *dest = "default destination";
    int index = 0x100;
    int verbose = 1;
    int badtype = 1;


    const copt_t OPTS[] =
    {
        {  0,  "infile",    INPUT_STR, { &infile },    "file to read from." },
        { 'o', "outfile",   INPUT_STR, { &outfile },   "file to write to." },
        { 'd', NULL,        INPUT_STR, { &dest },      "file to write to x2." },
        { 'i', "--index",   INPUT_INT, { &index },     "overwrite automotic indexing." },
        { 'v', "--verbose", FLAG_T,    { &verbose },   "log extra messages." },
        {  0,  "--terse",   FLAG_F,    { &verbose },   "log warnings and errors." },
        {  0,  "--color",   CALLBACK,  { copt_enable_colors_cb },  "enable pretty colours!" },
        {  0,  "--nocolor", CALLBACK,  { copt_disable_colors_cb }, "dont use any colours." },
        { 'h', "--help",    CALLBACK,  { usage_cb },   "show this page." },
        { 'V', "--version", CALLBACK,  { version_cb }, "show the version/copyright page." },
        {  0,  "--bad-type", 0x100,    { &badtype },   "this should throw a fatal error" },
    };
    const size_t OPT_CNT = sizeof (OPTS) / sizeof (*OPTS);
   
    int rc = 0;

    rc = copt_parser ((copt_t *)OPTS, OPT_CNT, argv+1, argc-1, NULL);
    if (rc == -1)
    {
        log_usage (stderr, (copt_t *)OPTS, OPT_CNT);
        exit (EXIT_FAILURE);
    }
    

    (void)fprintf (stdout, "results:\n");
    (void)fprintf (stdout, "  rc:      %d\n", rc);
    (void)fprintf (stdout, "  infile:  '%s'\n", infile);
    (void)fprintf (stdout, "  outfile: '%s'\n", outfile);
    (void)fprintf (stdout, "  dest:    '%s'\n", dest);
    (void)fprintf (stdout, "  index:   %d\n", index);
    (void)fprintf (stdout, "  verbose: %d\n", verbose);

    exit (EXIT_SUCCESS);
}






static void 
log_usage (FILE *output, copt_t *opts, size_t opt_cnt)
{
    char *printable_opts = copt_printable_opts (opts, opt_cnt);
    
    (void)fprintf (output, 
        "usage: argparser_ex <options>\n"
        "\n"
        "options:\n"
        "%s\n"
        "\n"
        "moreinfo here\n",
        printable_opts);
}


static void 
log_version (FILE *output)
{
    (void)fprintf (output, "version info\n");
}


/* end of file */
