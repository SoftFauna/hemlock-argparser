
#include "log.h"

#include "pretty.h"
#include "debug_trace.h"
#include "option.h"
#include "tokenizer.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>


static void log_warning_prefix (void);
static void log_error_prefix (void);
static void log_fatal_error_prefix (void);


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
    log_error_prefix ();
    (void)fprintf (stderr, 
            "unknown option '%s%s-%c%s%s'.\n", 
            g_bold, g_underline, short_opt, g_nounderline, g_nobold);
}


void
log_unknown_long_option (char *long_opt)
{
    char *opt_param_start = NULL;
    int opt_length = 0;

    TRACE_FN ();

    opt_param_start = strchr (long_opt, '=');
    opt_length = (int)(opt_param_start - long_opt);

    log_error_prefix ();
    (void)fprintf (stderr, "unknown option '%s%s%.*s%s%s'.\n", 
        g_bold, g_underline,
        opt_length, long_opt,
        g_nounderline, g_nobold
    );

}


void
log_missing_parameter (struct token *p_token)
{
    TRACE_FN ();
    log_error_prefix ();
    (void)fprintf (stderr, 
            "option '%s%s%s%s%s' expects a parameter of type %s%s<%s>%s%s, but none "
            "was given.\n",
            g_bold, g_cyan, get_option_name (p_token), g_fg_reset, g_nobold,
            g_bold, g_cyan, get_parameter_type_name (p_token->opt->type), g_fg_reset, g_nobold);
}


void
log_invalid_parameter_type (struct token *p_token)
{
    TRACE_FN ();
    log_error_prefix ();
    (void)fprintf (stderr, 
            "option '%s%s%s%s%s' expects a parameter of type %s%s<%s>%s%s, but got "
            "'%s%s%s%s%s'.\n",
            g_bold, g_cyan, get_option_name (p_token), g_fg_reset, g_nobold,
            g_bold, g_cyan, get_parameter_type_name (p_token->opt->type), g_fg_reset, g_nobold,
            g_bold, g_underline, p_token->argv_param, g_nounderline, g_nobold
    );
}


void
log_useless_parameter (struct token *p_token)
{
    TRACE_FN ();
    log_error_prefix ();
    (void)fprintf (stderr, 
            "option '%s%s%s%s%s' does not take any parameters, but got '%s%s%s%s%s'.\n",
            g_bold, g_cyan, get_option_name (p_token), g_fg_reset, g_nobold,
            g_bold, g_underline, p_token->argv_param, g_nounderline, g_nobold);
}

void
log_fatal_unknown_type (copt_type_t type)
{
    TRACE_FN ();
    log_fatal_error_prefix ();
    (void)fprintf (stderr, 
            "malformed option array, unknown parameter type %s%s%d%s%s\n",
            g_bold, g_underline, type, g_nounderline, g_nobold);
}


/* PRIVATE FILE-STATIC API */
static void 
log_warning_prefix (void)
{
    TRACE_FN ();
    (void)fprintf (stderr, 
            "%s%swarning%s%s: ",
            g_bold, g_yellow, 
            g_fg_reset, g_nobold
    );
}

static void 
log_error_prefix (void)
{
    TRACE_FN ();
    (void)fprintf (stderr, 
            "%s%serror%s%s: ",
            g_bold, g_red, 
            g_fg_reset, g_nobold
    );

}

static void 
log_fatal_error_prefix (void)
{
    TRACE_FN ();
    (void)fprintf (stderr, 
            "%s%s%sfatal error%s%s%s: ",
            g_bold, g_underline, g_red, 
            g_fg_reset, g_nounderline, g_nobold
    );
}


/* end of file */
