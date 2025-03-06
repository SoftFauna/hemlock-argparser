
#include "log.h"

#include "debug_trace.h"
#include "option.h"
#include "tokenizer.h"

#include <stddef.h>
#include <stdio.h>


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
    (void)fprintf (stderr, "error: unknown option '-%c'.\n", short_opt);
}


void
log_unknown_long_option (char *long_opt)
{
    TRACE_FN ();
    (void)fprintf (stderr, "error: unknown option '%s'.\n", long_opt);
}


void
log_missing_parameter (struct token *p_token)
{
    TRACE_FN ();
    (void)fprintf (stderr, 
            "error: option '%s' expects a parameter of type <%s>, but none was "
            "given.\n",
            get_option_name (p_token), 
            get_parameter_type_name (p_token->opt->type));
}


void
log_invalid_parameter_type (struct token *p_token)
{
    TRACE_FN ();
    (void)fprintf (stderr, 
            "error: option '%s' expects a parameter of type <%s>, but got "
            "parameter '%s'.\n",
            get_option_name (p_token), 
            get_parameter_type_name (p_token->opt->type),
            p_token->argv_param);
}


/* end of file */
