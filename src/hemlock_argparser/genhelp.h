
#pragma once

#include "option.h"

#include <stdio.h>
#include <stddef.h>


char *gen_usage (copt_t *opt_arr, size_t opt_cnt, int wrap_col);
char *gen_help_page (copt_prog_t *prog, int wrap_col);
char *gen_version_page (copt_prog_t *prog);

/* end of file */
