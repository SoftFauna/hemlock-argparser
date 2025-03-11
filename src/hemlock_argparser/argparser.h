/* hemlock-argparser - a generic arguement parser written for HEMLOCK.
 * <https://github.com/SoftFauna/hemlock-argparser.git>
 * Copyright (c) 2025 The SoftFauna Team
 * MIT License */

#ifndef HMARG_ARGPARSER_HEADER
#define HMARG_ARGPARSER_HEADER
#ifdef __cplusplus
extern "C" {
#endif
 

#include "option.h"

#include <stdio.h>
#include <stddef.h>

/* handle windows msvc shenanigans */
#if defined _WIN32 || defined __CYGWIN__
#   ifdef LIB_HEMARG_EXPORTS
#       define LIB_HEMARG_API __declspec(dllexport)
#   else
#       define LIB_HEMARG_API __declspec(dllimport)
#   endif
#else
#   ifdef LIB_HEMARG_EXPORTS
#       define LIB_HEMARG_API __attribute__ ((visibility ("default")))
#   else
#       define LIB_HEMARG_API
#   endif
#endif

/* api */
LIB_HEMARG_API int copt_parser (copt_t *option_array, size_t option_count, char **argv, size_t argc, void *cb_data);

LIB_HEMARG_API char *copt_print_options (copt_t *option_array, size_t option_count, int wrap_col);

LIB_HEMARG_API char *copt_help_page (copt_prog_t *program, int wrap_col);

LIB_HEMARG_API char *copt_version_page (copt_prog_t *program);

LIB_HEMARG_API int copt_enable_colors_cb (copt_t *option_array, size_t option_count, void *cb_data);

LIB_HEMARG_API int copt_disable_colors_cb (copt_t *option_array, size_t option_count, void *cb_data);

LIB_HEMARG_API int copt_are_colors_enabled (void);


#ifdef __clplusplus
}
#endif /* C++ compat */
#endif /* header guard */
/* end of file */
