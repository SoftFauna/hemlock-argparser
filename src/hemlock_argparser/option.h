/* hemlock-argparser - a generic arguement parser written for HEMLOCK.
 * <https://github.com/SoftFauna/hemlock-argparser.git>
 * Copyright (c) 2025 The SoftFauna Team
 * MIT License */

/**
 * @file
 * Define every typedef, structure, and enum necessary for propper use of 
 * the Hemlock Arguement Parser.
 */

#ifndef HMARG_OPTION_HEADER
#define HMARG_OPTION_HEADER
#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>


/* this is required, otherwise when we get to defining copt_cb_t, the copt_t 
 * type will be missing and we will get all kinds of errors */
typedef struct copt copt_t;


/**
 * option type enumerator, paired with copt specifies which type of 
 * variable/callback to write to. 
 * 
 * @see copt_return_t
 * @see copt_t
 * @see copt_parser()
 */
typedef enum
{
    CONARG_TYPE_NULL = 0,   /**< no type specified, type error      */
    INPUT_INT,              /**< specifys a return type of int*     */
    INPUT_STR,              /**< specifys a return type of char**   */
    FLAG_T,                 /**< specifys a return type of int*     */
    FLAG_F,                 /**< specifys a return type of int*     */
    CALLBACK,               /**< specifys a callback function       */
    CONARG_TYPE_CNT,        /**< total number of types, counter     */
} copt_type_t;


/**
 * Defines an option callback function. executed by copt_parser, if a 
 * matching arguement is reached and the option is of type CALLBACK, the 
 * paired callback funtion is executed on the spot.
 * 
 * The callback function is expected to take the option_array, option_count, 
 * and some abstract cb_data, each of which are provided by the user when 
 * calling copt_parser.
 * 
 * Additionally, a return of COPT_CB_SUCCESS is indicitive of a success, and 
 * COPT_CB_FAILURE of a failure.
 * 
 * @see copt_cb_return_t
 * @see copt_type_t
 * @see copt_t
 * @see copt_parser()
 */
typedef int (*copt_cb_t)(copt_t *option_arr, size_t option_cnt, void *cb_data);


/**
 * Returned value of copt_cb_t callback function to indiciate a successful 
 * operation or failure. on failure program is aborted.
 * 
 * @see copt_cb_t;
 */
typedef enum 
{
    COPT_CB_SUCCESS = 0,    /**< callback exitted with a success. */ 
    COPT_CB_FAILURE = -1,   /**< callback exitted with a failure. */
} copt_cb_return_t;


/**
 * When used in tandom with copt_type_t as an identifier, copt_return_t 
 * speicifies where the result of an option/flag should be stored.
 * 
 * @see copt_t
 * @see copt_cb_t
 * @see copt_type_t
 */
typedef union 
{
    void *return_ptr;       /**< unused, allow for indirect pointer casts */
    char **p_str;           /**< specify a const string return */
    int *p_int;             /**< specify an integer/boolean return. */
    copt_cb_t cb_fn;        /**< specify an external callback. */
} copt_return_t;


/**
 * Defines a parsable option/flag, complete with short, long, return type, and
 * description. Typically, functions expect an array of options to be provided
 * each following this format.
 * 
 * @see copt_type_t
 * @see copt_return_t
 * @see copt_parser()
 */
typedef struct copt
{
    char short_opt;         /**< short option single character. */
    char *long_opt;         /**< long option string. */
    copt_type_t type;       /**< option return type. */
    copt_return_t m;        /**< option return variable/pointer */
    char *desc;             /**< description of the options */
} copt_t;


/**
 * Define the template information for a program. including rudimentory 
 * information such as the name, version, description, and copyright.
 * Additionally, stores a pointer array options/flags the program can 
 * accept. Used primarily by copt_help_page andcopt_version_page, acting
 * as an object to hold all the static information they need.
 * 
 * @see copt_t
 * @see copt_help_page()
 * @see copt_version_page()
 */
typedef struct
{
    char *name;                 /**< the program's name. */
    char *description;          /**< a description of the program. */
    char *version;              /**< the programs's version. */

    char *help_extra;           /**< (optional) print with the help page. */
    char *version_extra;        /**< (optional) print with the version page. */

    char *copyright_year;       /**< year of the program's copyright. */
    char *copyright_holder;     /**< the name of the copyright holder. */
    char *license_name;         /**< the name of the license. */
    char *license_url;          /**< a link to the license. */

    char *issues_url;           /**< where to send issues/bugreports to. */
    char *repository_url;       /**< link to the program's source repo. */
    char *contact_email;        /**< provided contact method. */
    char *contact_name;         /**< main contact's name. */

    copt_t *options;            /**< an array of parsable options. */
    size_t  option_count;       /**< lenght of the option array. */
} copt_prog_t;


#ifdef __clplusplus
}
#endif /* C++ compat */
#endif /* header guard */
/* end of file */
