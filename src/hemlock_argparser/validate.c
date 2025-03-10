

#include "validate.h"

#include "debug_trace.h"
#include "log.h"
#include "option.h"
#include "parser.h"
#include "tokenizer.h"

#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int is_valid_str (char *maybe_str);
int is_valid_int (char *maybe_int);
int validate (struct tokenizer *self);

/* PUBLIC API */
int
validate (struct tokenizer *self)
{
    size_t i = 0;
    struct token *p_token = NULL;
    copt_t *p_opt = NULL;

    int valid = 1;
    
    TRACE_FN ();

    for (; i < self->count; i++)
    {
        p_token = &self->token_arr[i];
        p_opt = p_token->opt;

        /* skip all items that dont take a parameter */
        if (!takes_parameter (p_opt->type))
        {
            continue;
        }

        /* validate by data type */
        switch (p_opt->type)
        {
        case INPUT_INT:
            valid = is_valid_int (p_token->argv_param);
            break;

        case INPUT_STR:
            valid = is_valid_str (p_token->argv_param);
            break;

        default:
            valid = 0;
            break;
        }
        
        /* if invalid log and exit */
        if (!valid)
        {
            log_invalid_parameter_type (p_token);
            return -1;
        }
    }

    /* return 0 for all valid */
    return 0;
}


int 
is_valid_str (char *maybe_str)
{
    TRACE_FN ();
    return (maybe_str != NULL);
}


int
is_valid_int (char *maybe_int)
{
    char *remainder = NULL;
    long result_long = 0;

    TRACE_FN ();
    /* try converting using strtol */
    result_long = strtol (maybe_int, &remainder, 0);

    /* if the whole string was proccessed */
    if ((remainder == NULL) ||
        (*remainder != '\0'))
    {
        return 0;
    }

    /* if the result is too large for an integer */
    if ((result_long > INT_MAX) ||
        (result_long < INT_MIN))
    {
        return 0;
    }
    

    /* if all guards are passed, then it is valid */
    return 1;
}


/* end of file */
