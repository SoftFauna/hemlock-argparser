
#include "tokenizer.h"

#include "log.h"
#include "option.h"
#include "parser.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* PUBLIC API */
int
add_token (struct tokenizer *self, struct token token)
{
    const size_t INITIAL_ALLOC = 2;
    size_t tmp_size = 0;
    void *tmp = NULL;

    /* if tokenizer is not setup */
    if (self->token_arr == NULL)
    {
        tmp_size = INITIAL_ALLOC;

        self->token_arr = malloc (sizeof (struct token) * tmp_size);
        if (self->token_arr == NULL) { return -1; }

        self->alloc = tmp_size;
        self->count = 0;
    }


    /* extend the dynamic array if necessary */
    while (self->count >= self->alloc)
    {
        tmp_size = self->alloc * 2;
        tmp = realloc (self->token_arr, (sizeof (struct token) * tmp_size));
        if (tmp == NULL) { return -1; }

        self->token_arr = tmp;
        self->alloc = tmp_size;
    }

    /* add token to array */
    self->token_arr[self->count] = token;

    return 0;
}


void
destroy_tokenizer (struct tokenizer *self)
{
    if (self == NULL) { return; }

    free (self->token_arr);
    self->token_arr = NULL;
    self->alloc = 0;
    self->count = 0;

    return;
}


copt_t *
get_long_option (char *cursor, copt_t *opt_arr, size_t opt_cnt)
{
    while (opt_cnt > 0)
    {
        /* skip cases where an long opt is not given */
        if (opt_arr->long_opt == NULL) { continue; }

        /* if a match is found return a poitner */
        if (strcmp (cursor, opt_arr->long_opt) == 0)
        {
            return opt_arr;
        }

        /* increment along options */
        opt_cnt--;
        opt_arr++;
    }

    /* otherwise return NULL */
    return NULL;
}


copt_t *
get_short_option (char character, copt_t *opt_arr, size_t opt_cnt)
{
    for (; opt_cnt > 0; opt_cnt--, opt_arr++)
    {
        /* skip cases where a short is not given */
        if (opt_arr->short_opt == '\0') { continue; }

        /* check if match, return option matched */
        if (character == opt_arr->short_opt)
        {
            return opt_arr;
        }
    }

    /* if no match, return NULL */
    return NULL;
}


int
tokenize (struct tokenizer *self, char **argv, size_t argc, 
          copt_t *opt_arr, size_t opt_cnt)
{
    size_t arr_index  = 0;
    char *iter = NULL;

    struct token token = { 0 };
    copt_t *opt_match = NULL;


    while (arr_index < argc)
    {
        token = (struct token){ 0 };
        iter = argv[arr_index];
        arr_index++;

        /* get option */
        /* check for long options*/
        opt_match = get_long_option (iter, opt_arr, opt_cnt);
        if (opt_match != NULL)
        {
            /* add long options */
            token.type     = TOKEN_OPT_LONG;
            token.opt      = opt_match;
            token.argv_opt = iter;

            /* move cursor just after the option */
            iter += strlen (token.opt->long_opt);
        }
        else if (*iter == '-')
        {
            /* check for short options */
            iter++;
            while (*iter != '\0')
            {
                opt_match = get_short_option (*iter, opt_arr, opt_cnt);

                /* if no option is found, fall throught to no option found */
                if (opt_match == NULL)
                {
                    break;
                }

                /* add short options */
                token.type     = TOKEN_OPT_SHORT;
                token.opt      = opt_match;
                token.argv_opt = iter;
            
                /* move cursor just after the option */
                iter++; 

                /* if a short option takes a paraemter accept no more short 
                 * options and let add_token get handled after parameter is 
                 * found. */
                if (takes_parameter (token.opt->type))
                {
                    break;
                }
                
                /* if no parameter is required, we can add the option now */
                add_token (self, token);
            }
        }

        /* no option found */
        if (opt_match == NULL)
        {
            /* unknown option */
            log_unknown_option (iter);
            destroy_tokenizer (self);
            return -1;
        }

        /* skip "get parameter" section if none is required */
        if (!takes_parameter (opt_match->type))
        {
            continue;
        }

        /* get parameter */
        if (*iter == '=')
        {
            iter++;
        }
        else if ((*iter == '\0') &&
                 (arr_index <= argc))
        {
            iter = argv[arr_index];
        }
        else
        {
            /* missing parameter */
            log_missing_parameter (&token);
            destroy_tokenizer (self);
            return -1;
        }
        
        /* add param */
        token.argv_param = iter;

        /* then add the taken to the tokenizer */
        add_token (self, token);
    }

    return 0;
}


/* end of file */