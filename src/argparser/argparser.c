
#include "argparser.h"

#include "debug_trace.h"
#include "finish.h"
#include "genhelp.h"
#include "pretty.h"
#include "tokenizer.h"
#include "unused_param.h"
#include "validate.h"

#include <stddef.h>
#include <stdio.h>


/* PUBLIC API */
int 
copt_parser (copt_t *opt_arr, size_t opt_cnt, char **argv, size_t argc, 
             void *cb_data)
{
    struct tokenizer tokens = { 0 };
    int rc = 0;

    TRACE_FN ();

    /* if no arguements are given report an error */
    if (argc == 0)
    {
        return -1;
    }

    /* if any of the following step fail, set returncode to a fail stats */
    if ((tokenize (&tokens, argv, argc, opt_arr, opt_cnt, cb_data)) || 
        (validate (&tokens)) ||
        (finish (&tokens)))
    {
        rc = -1;
    }

    /* clean up memeory */
    destroy_tokenizer (&tokens);
    return rc;
}


int 
copt_enable_colors_cb (copt_t *opt_arr, size_t opt_cnt, void *cb_data)
{
    TRACE_FN ();
    CB_UNUSED_PARAM (opt_arr);
    CB_UNUSED_PARAM (opt_cnt);
    CB_UNUSED_PARAM (cb_data);
    cprintf_enable ();    
    return 0;
}


int
copt_disable_colors_cb (copt_t *opt_arr, size_t opt_cnt, void *cb_data)
{
    TRACE_FN ();
    CB_UNUSED_PARAM (opt_arr);
    CB_UNUSED_PARAM (opt_cnt);
    CB_UNUSED_PARAM (cb_data);
    cprintf_disable ();    
    return 0;
}


int 
copt_are_colors_enabled (void)
{
    TRACE_FN ();
    return cprintf_get_status ();
}

char *
copt_print_options (copt_t *opt_arr, size_t opt_cnt)
{
    TRACE_FN ();
    return genhelp (opt_arr, opt_cnt);
}


/* PRIVATE API */


/* end of file */
