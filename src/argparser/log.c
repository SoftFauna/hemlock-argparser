
#include "log.h"

#include "pretty.h"
#include "debug_trace.h"
#include "option.h"
#include "tokenizer.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define WARNING_PREFIX "%Ab%Fywarning%Ar: "
#define ERROR_PREFIX "%Ab%Frerror%Ar: "
#define FATAL_PREFIX "%Ab%Au%Frfatal error%Ar: "


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
            ERROR_PREFIX "unknown option '%Ab%Au-%c%Ar'.\n", 
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
            ERROR_PREFIX "unknown option '%Ab%Au%.*s%Ar'.\n", 
            opt_length, long_opt);

}


void
log_missing_parameter (struct token *p_token)
{
    TRACE_FN ();

    (void)cfprintf (stderr, 
            ERROR_PREFIX "option '%Ab%Fc%s%Ar' expects a parameter of type "
            "%Ab%Fc<%s>%Ar, but none was given.\n",
            get_option_name (p_token),
            get_parameter_type_name (p_token->opt->type));
}


void
log_invalid_parameter_type (struct token *p_token)
{
    TRACE_FN ();

    (void)cfprintf (stderr, 
            ERROR_PREFIX "option '%Ab%Fc%s%Ar' expects a parameter of type "
            "%Ab%Fc<%s>%Ar, but got '%Ab%Au%s%Ar'.\n",
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
            ERROR_PREFIX "option '%Ab%Fc%s%Ar' does not take any parameters, "
            "but got '%Ab%Au%s%Ar'.\n",
            get_option_name (p_token),
            p_token->argv_param);
}

void
log_fatal_unknown_type (copt_type_t type)
{
    TRACE_FN ();

    (void)cfprintf (stderr, 
            FATAL_PREFIX "malformed option array, unknown parameter type "
            "%Ab%Au%d%Ar\n",
            type);
}


/* PRIVATE FILE-STATIC API */


/* end of file */
