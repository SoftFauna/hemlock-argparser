
#include "argparser.h"

#include "debug_trace.h"
#include "finish.h"
#include "tokenizer.h"
#include "validate.h"

#include <stddef.h>


/* PUBLIC API */
int 
copt_parser (copt_t *opt_arr, size_t opt_cnt, char **argv, size_t argc, 
             void *cb_data)
{
    struct tokenizer tokens = { 0 };
    int rc = 0;

    TRACE_FN ();

    /* if any of the following step fail, set returncode to a fail stats */
    if ((tokenize (&tokens, argv, argc, opt_arr, opt_cnt)) || 
        (validate (&tokens)) ||
        (finish (&tokens, opt_arr, opt_cnt, cb_data)))
    {
        rc = -1;
    }

    /* clean up memeory */
    destroy_tokenizer (&tokens);
    return rc;
}

char *
copt_printable_opts (copt_t *opt_arr, size_t opt_cnt)
{
    TRACE_FN ();
    return NULL;
}


/* PRIVATE API */


/* end of file */
