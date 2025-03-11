/* hemlock-argparser - a generic arguement parser written for HEMLOCK.
 * <https://github.com/SoftFauna/hemlock-argparser.git>
 * Copyright (c) 2025 The SoftFauna Team
 * MIT License */

/**
 * @file
 * The main Hemlock Arguement Parser API. Defines every public API call, how 
 * to use them, and how they should be called. The main interface for the 
 * library.
 */

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


/**
 * Completely proccess a program's argv+argc, against a predefined set of
 * options. The option_array is a pointer array of 
 * [copt_t](#copt_t) objects defining all valid options. 
 * The option_count is the length of option_array. cb_data is a void* passed 
 * as data to an option's callback function.
 * 
 * @param option_array an array of supported options/flags.
 * @param option_count length of option_array.
 * @param argv         arguement list.
 * @param argc         arguement count.
 * @param cb_data      a void* to pass to any callback functions.
 * 
 * @return 0 on a success, -1 on failure.
 * 
 * @see copt_t
 */
LIB_HEMARG_API int copt_parser (copt_t *option_array, size_t option_count, 
        char **argv, size_t argc, void *cb_data);


/**
 * Given an array of copt_ts, option_array, generate a program's option 
 * documentation. The resulting print-optimized string is heap allocated; 
 * caller takes responisibility for cleanup. wrap_col specifies the column at 
 * which the option/flag's descriptions should wrap. if wrap_col is 0 no pretty
 * wrapping will occur. If color is enabled, the generated string will use 
 * ANSI escape codes to print beautifully.
 * 
 * options's use format:
 * ```text
 *  -d, --description-example    description line one. continue the first line 
 *                                 and then pretty wrap description to 80
 *                                 columns.
 *  -a                           short flag.
 *  -b=<parameter>               short input option.
 *      --long_a                 long flag.
 *      --long_b=<parameter>     long input option.
 *  -c, --long_c                 short and long flags.
 *  -d, --long_d=<parameter>     short and long input option.
 * ```
 * 
 * @param option_array an array of options/flags to be parsed.
 * @param option_count the length of option_array.
 * @param wrap_col     the column to pretty wrap outputs to.
 * 
 * @return a caller-owned heap-allocated string documenting what options are 
 *           provided by option_array.
 * 
 * @see copt_t
 * @see copt_enable_color_cb()
 * @see copt_disable_color_cb()
 */
LIB_HEMARG_API char *copt_print_options (copt_t *option_array, 
        size_t option_count, int wrap_col);


/**
 * Given a set of program information, copt_prog_t, generate a program's help 
 * page. The resulting print-optimized string is heap allocated; caller takes 
 * responisibility for cleanup. wrap_col specifies the column at which the 
 * option/flag's descriptions should wrap. if wrap_col is 0 no pretty wrapping 
 * will occur. If color is enabled, the generated string will use ANSI escape 
 * codes to print beautifully.
 * 
 * @param program  some basic information about the program: name, 
 *                   license, accepted options, ect..
 * @param wrap_col the column to pretty wrap output to.
 * 
 * @return a caller-owned heap-allocated string documenting the program's
 *           help page.
 * 
 * @see copt_prog_t
 * @see copt_enable_color_cb()
 * @see copt_disable_color_cb()
 */
LIB_HEMARG_API char *copt_help_page (copt_prog_t *program, int wrap_col);


/**
 * Given a set of program information, copt_prog_t, generate a program's 
 * version page. The resulting print-optimized string is heap allocated; 
 * caller takes responisibility for cleanup. If color is enabled, the 
 * generated string will use ANSI escape codes to print beautifully.
 * 
 * @param program  some basic information about the program: name, 
 *                   license, accepted options, ect..
 * 
 * @return a caller-owned heap-allocated string documenting the program's 
 *           version page.
 * 
 * @see copt_prog_t
 * @see copt_enable_color_cb()
 * @see copt_disable_color_cb()
 */
LIB_HEMARG_API char *copt_version_page (copt_prog_t *program);


/**
 * Check if colors are enabled/disabled. Return a boolean. 
 * 
 * @return 0 if disabled, 1 if enabled.
 * 
 * @see copt_enable_colors_cb()
 * @see copt_disable_colors_cb()
 */
LIB_HEMARG_API int copt_are_colors_enabled (void);


/**
 * A callback for enabling coloured printing of error messages, help page, 
 * and version page generation. Used in conjunction with copt_t CALLBACK, 
 * enables colors when a user defined option is encountered.
 * 
 * @param option_array ignored
 * @param option_count ignored
 * @param cb_data      ignored
 * 
 * @return COPT_CB_SUCCESS or COPT_CB_FAILURE depending on success/failure.
 * 
 * @see copt_t 
 * @see copt_cb_t
 * @see copt_cb_return_t
 * @see copt_parser()
 */
LIB_HEMARG_API int copt_enable_colors_cb (copt_t *option_array, 
        size_t option_count, void *cb_data);


/**
 * A callback for diabling coloured printing of error messages, help page, 
 * and version page generation. Used in conjunction with copt_t CALLBACK, 
 * disables colors when a user defined option is encountered.
 * 
 * @param option_array ignored
 * @param option_count ignored
 * @param cb_data      ignored
 * 
 * @return COPT_CB_SUCCESS or COPT_CB_FAILURE depending on success/failure.
 * 
 * @see copt_t 
 * @see copt_cb_t
 * @see copt_cb_return_t
 * @see copt_parser()
 */
LIB_HEMARG_API int copt_disable_colors_cb (copt_t *option_array, 
        size_t option_count, void *cb_data);


#ifdef __clplusplus
}
#endif /* C++ compat */
#endif /* header guard */
/* end of file */
