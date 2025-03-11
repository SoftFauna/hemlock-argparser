
#include "log.h"

#include "colors.h"
#include "debug_trace.h"
#include "option.h"
#include "pretty.h"
#include "tokenizer.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define WARNING_PREFIX C_WARN"warning"C_RESET": "
#define ERROR_PREFIX   C_ERROR"error"C_RESET": "
#define FATAL_PREFIX   C_FATAL"fatal error"C_RESET": "


/* PUBLIC API */
char *
get_parameter_type_name (copt_type_t type)
{
    TRACE_FN ();

    switch (type)
    {
    case INPUT_INT:
        return "number";

    case INPUT_STR:
        return "string";

    default:
        return "error_unknown_type";
    }
}


char *
get_option_name (struct token *p_token)
{
    const int SHORT_OPT_INDEX = 1;
    static char s_short_opt[] = "- "; /* persist after return */

    char *opt_name = NULL;

    TRACE_FN ();

    if (p_token->type == TOKEN_OPT_SHORT)
    {
        opt_name = s_short_opt;
        opt_name[SHORT_OPT_INDEX] = p_token->opt->short_opt;
    }
    else if (p_token->type == TOKEN_OPT_LONG)
    {
        opt_name = p_token->opt->long_opt;
    }

    return opt_name;
}


void
log_unknown_short_option (char short_opt)
{
    TRACE_FN ();

    (void)cfprintf (stderr, 
            ERROR_PREFIX "unknown option "C_OPTION"-%c"C_RESET".\n", 
            short_opt);
}


void
log_unknown_long_option (char *long_opt)
{
    char *opt_param_start = NULL;
    int opt_length = 0;

    TRACE_FN ();

    opt_param_start = strchr (long_opt, '=');
    opt_length = (int)(opt_param_start - long_opt);

    (void)cfprintf (stderr, 
            ERROR_PREFIX "unknown option "C_OPTION"'%.*s'"C_RESET".\n", 
            opt_length, long_opt);

}


void
log_missing_parameter (struct token *p_token)
{
    TRACE_FN ();

    (void)cfprintf (stderr, 
            ERROR_PREFIX "option "C_OPTION"'%s'"C_RESET" expects a parameter "
            "of type "C_PARAM"<%s>"C_RESET", but none was given.\n",
            get_option_name (p_token),
            get_parameter_type_name (p_token->opt->type));
}


void
log_invalid_parameter_type (struct token *p_token)
{
    TRACE_FN ();

    (void)cfprintf (stderr, 
            ERROR_PREFIX "option "C_OPTION"'%s'"C_RESET" expects a parameter "
            "of type "C_PARAM"<%s>"C_RESET", but got "C_PARAM"'%s'"C_RESET
            ".\n",
            get_option_name (p_token),
            get_parameter_type_name (p_token->opt->type),
            p_token->argv_param
    );
}


void
log_useless_parameter (struct token *p_token)
{
    TRACE_FN ();

    (void)cfprintf (stderr, 
            ERROR_PREFIX "option "C_OPTION"'%s'"C_RESET" does not take any "
            "parameters, but got "C_PARAM"'%s'"C_RESET".\n",
            get_option_name (p_token),
            p_token->argv_param);
}

void
log_fatal_unknown_type (copt_type_t type)
{
    TRACE_FN ();

    (void)cfprintf (stderr, 
            FATAL_PREFIX "malformed option array, unknown parameter type "
            C_PARAM"%d"C_RESET"\n",
            type);
}


/* PRIVATE FILE-STATIC API */


/* end of file */
