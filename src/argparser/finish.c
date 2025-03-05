
#include "finish.h"

#include "option.h"
#include "tokenizer.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/* PUBLIC API */
int
finish (struct tokenizer *self, copt_t *opt_arr, size_t opt_cnt, void *cb_data)
{
    int rc = 0;
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
            rc = opt->m.cb_fn (opt_arr, opt_cnt, cb_data);
            if (rc != 0)
            {
                return -1;
            }
            break;

        default:
            /* error bad option type */
            (void)fprintf (stderr, "fatal error: finish(): bad return type %d\n", 
                           opt->type);
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