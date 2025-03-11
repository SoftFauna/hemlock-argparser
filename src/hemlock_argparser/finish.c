/* hemlock-argparser - a generic arguement parser written for HEMLOCK.
 * <https://github.com/SoftFauna/hemlock-argparser.git>
 * Copyright (c) 2025 The SoftFauna Team
 * MIT License */

#include "finish.h"

#include "debug_trace.h"
#include "log.h"
#include "option.h"
#include "tokenizer.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/* PUBLIC API */
int
finish (struct tokenizer *self)
{
    size_t i = 0;
    struct token *iter = NULL;
    copt_t *opt = NULL;

    TRACE_FN ();

    for (; i < self->count; i++)
    {
        iter = &self->token_arr[i];
        opt  = iter->opt;

        /* if no return pointer is given, throw a fit */
        if (opt->m.return_ptr == NULL)
        {
            return -1;
        }

        /* otherwise, return the parameters in propper formats */
        switch (opt->type)
        {
        case INPUT_INT:
            *opt->m.p_int = to_int (iter->argv_param);
            break;

        case INPUT_STR:
            *opt->m.p_str = iter->argv_param;
            break;

        case FLAG_T:
            *opt->m.p_int = 1;
            break;

        case FLAG_F:
            *opt->m.p_int = 0;
            break;

        case CALLBACK:
            /* callbacks are executed as they are found (in the tokenizer),
             * previously they were handled here, however to work around 
             * executing --help as it is reached, aswell as to apply colours 
             * to error reports, it was moved to execute as they are found. */
            break;

        default:
            log_fatal_unknown_type (opt->type);
            return -1;
        }
        iter++;
    }

    return 0;
}


int
to_int (char *int_string)
{
    TRACE_FN ();
    return (int)strtol (int_string, NULL, 0);
}


/* end of file */
