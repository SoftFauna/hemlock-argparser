/* hemlock-argparser example - a generic arguement parser written for HEMLOCK.
 * <https://github.com/SoftFauna/hemlock-argparser.git>
 * Copyright (c) 2025 The SoftFauna Team
 * MIT License */

#ifndef HMARGEX_CLI_HEADER
#define HMARGEX_CLI_HEADER
#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    char *infile;
    char *outfile;
    char *dest;
    int index;
    int verbose;
    int badtype;
    int reasonable;
    int too_long_a;
    int too_long_b;
} cli_results_t;


void cli_parser (int argc, char **argv, cli_results_t *cli_results);

#ifdef __clplusplus
}
#endif /* C++ compat */
#endif /* header guard */
/* end of file */

