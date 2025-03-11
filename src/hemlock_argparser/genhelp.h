/* hemlock-argparser - a generic arguement parser written for HEMLOCK.
 * <https://github.com/SoftFauna/hemlock-argparser.git>
 * Copyright (c) 2025 The SoftFauna Team
 * MIT License */

#ifndef HMARG_GENHELP_HEADER
#define HMARG_GENHELP_HEADER
#ifdef __cplusplus
extern "C" {
#endif
 

#include "option.h"

#include <stdio.h>
#include <stddef.h>


char *gen_usage (copt_t *opt_arr, size_t opt_cnt, int wrap_col);
char *gen_help_page (copt_prog_t *prog, int wrap_col);
char *gen_version_page (copt_prog_t *prog);

#ifdef __clplusplus
}
#endif /* C++ compat */
#endif /* header guard */
/* end of file */
