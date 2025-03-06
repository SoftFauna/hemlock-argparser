
#pragma once

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
LIB_HEMARG_API int copt_parser (copt_t *opt_arr, size_t opt_cnt, char **argv, size_t argc, void *cb_data);

LIB_HEMARG_API void copt_print_options (FILE *output, copt_t *opt_arr, size_t opt_cnt);

LIB_HEMARG_API int copt_enable_colors_cb (copt_t *opt_arr, size_t opt_cnt, void *cb_data);
LIB_HEMARG_API int copt_disable_colors_cb (copt_t *opt_arr, size_t opt_cnt, void *cb_data);

LIB_HEMARG_API int copt_are_colors_enabled (void);

/* end of file */