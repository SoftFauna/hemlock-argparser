/* hemlock-argparser example - a generic arguement parser written for HEMLOCK.
 * <https://github.com/SoftFauna/hemlock-argparser.git>
 * Copyright (c) 2025 The SoftFauna Team 
 * MIT License */


#include "cli.h"

#include <hemlock_argparser/argparser.h>
#include <hemlock_argparser/unused_param.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static copt_t *get_options (size_t *p_size, cli_results_t *cli_results);
static copt_prog_t *get_program (copt_t *options, size_t option_count);

static int help_cb (int argc, char **argv, copt_t *opt, void *cb_data);
static int version_cb (int argc, char **argv, copt_t *opt, void *cb_data);

static void help_page (FILE *output, copt_prog_t *data);
static void version_page (FILE *output, copt_prog_t *data);


/* PUBLIC API */
void 
cli_parser (int argc, char **argv, cli_results_t *cli_results)
{
    int rc = 0;
    copt_t *options = NULL;
    size_t  option_count = 0;
    copt_prog_t *program = NULL;

    /* skip the execuable name */
    argv++;
    argc--;

    /* parse the options */
    options = get_options (&option_count, cli_results);
    program = get_program (options, option_count);

    rc = copt_parser (options, option_count, argv, argc, program);

    /* if the parser has an error, print help page to stderr */
    if (rc == -1)
    {
        help_page (stderr, program);
        exit (EXIT_FAILURE);
    }

    /* clean up */
    free (options);
    options = NULL;
    option_count = 0;
    program->options = NULL;
    program->option_count = 0;

    free (program);
    program = NULL;
}


/* PRIVATE API */
static copt_t *
get_options (size_t *p_length, cli_results_t *cli_results) 
{
    const copt_t CLI_OPTIONS[] =
    {
        {  0,  "infile",    INPUT_STR, { &cli_results->infile },    "file to read from." },
        { 'o', "outfile",   INPUT_STR, { &cli_results->outfile },   "file to write to." },
        { 'd', NULL,        INPUT_STR, { &cli_results->dest },      "file to write to x2." },
        { 'i', "--index",   INPUT_INT, { &cli_results->index },     "overwrite automotic indexing." },
        { 'v', "--verbose", FLAG_T,    { &cli_results->verbose },   "log extra messages." },
        {  0,  "--terse",   FLAG_F,    { &cli_results->verbose },   "log warnings and errors." },
        {  0,  "--color",   CALLBACK,  { .cb_fn = copt_enable_colors_cb },  "enable pretty colours!" },
        {  0,  "--nocolor", CALLBACK,  { .cb_fn = copt_disable_colors_cb }, "dont use any colours." },
        { 'h', "--help",    CALLBACK,  { .cb_fn = help_cb },      "show this page." },
        { 'V', "--version", CALLBACK,  { .cb_fn = version_cb },   "show the version/copyright page." },
        {  0,  "--bad-type", 0x100,    { &cli_results->badtype }, "this should throw a fatal error" },
        {  0, "--this-is-too-long-to-be-reasonable",      FLAG_T, { &cli_results->too_long_a}, "log extra messages." },
        {  0, "--this-is-also-too-long-to-be-reasonable", FLAG_T, { &cli_results->too_long_b}, "log extra messages and do about 999999999999999999999999 other things but we dont care about any of them, we are just looking for a really long line to test how wrapping text works with the parser." },
        {  0, "---reasonable",                            FLAG_T, { &cli_results->reasonable}, "log extra messages and do about 999999999999999999999999 other things but we dont care about any of them, we are just looking for a really long line to test how wrapping text works with the parser." },
    };

    copt_t *result = NULL;
    result = malloc (sizeof (CLI_OPTIONS));
    (void)memcpy (result, CLI_OPTIONS, sizeof (CLI_OPTIONS));

    *p_length = sizeof (CLI_OPTIONS) / sizeof (*CLI_OPTIONS);
    return result;
}


static copt_prog_t *
get_program (copt_t *opts, size_t opt_cnt) 
{    
    const copt_prog_t MY_PROGRAM = 
    {
        .name             = "hemlock_argparser_ex",
        .description      = "Demonstration program for hemlock-argparser.",
        .version          = "0.2.2",

        .copyright_year   = "2025",
        .copyright_holder = "The SoftFauna Team",
        .license_name     = "MIT",
        .license_url      = "https://mit-license.org/",
        .version_extra    = NULL,

        .issues_url       = "https://github.com/SoftFauna/hemlock-argparser",
        .repository_url   = "https://github.com/SoftFauna/hemlock-argparser",
        .contact_name     = "Sage I. Hendricks",
        .contact_email    = "sage.message@email.com",
        .help_extra       = NULL,

        .options          = opts,
        .option_count     = opt_cnt,
    };

    copt_prog_t *result = NULL;
    result = malloc (sizeof (MY_PROGRAM));
    memcpy (result, &MY_PROGRAM, sizeof (MY_PROGRAM));

    return result;
}


static void
help_page (FILE *output, copt_prog_t *prog)
{
    char *help_msg = NULL;
    const int WRAP_COL = 80;

    help_msg = copt_help_page (prog, (int)WRAP_COL);
    (void)fprintf (output, "%s\n", help_msg);

    free (help_msg);
    help_msg = NULL;
}


static void
version_page (FILE *output, copt_prog_t *prog)
{
    char *version_msg = NULL;

    version_msg = copt_version_page (prog);
    (void)fprintf (output, "%s\n", version_msg);

    free (version_msg);
    version_msg = NULL;
}


/* CALLBACK */
static int
help_cb (int argc, char **argv, copt_t *opt, void *cb_data)
{
    CB_UNUSED_PARAM (argc);
    CB_UNUSED_PARAM (argv);
    CB_UNUSED_PARAM (opt);
    
    help_page (stdout, (copt_prog_t *)cb_data);
    exit (EXIT_SUCCESS);     
}


static int
version_cb (int argc, char **argv, copt_t *opt, void *cb_data)
{
    CB_UNUSED_PARAM (argc);
    CB_UNUSED_PARAM (argv);
    CB_UNUSED_PARAM (opt);

    version_page (stdout, (copt_prog_t *)cb_data);
    exit (EXIT_SUCCESS);     
}


/* end of file */

