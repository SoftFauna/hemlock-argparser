
#pragma once

#include "option.h"

#include <stddef.h>


enum token_type
{
    TOKEN_UNKNOWN,
    TOKEN_OPT_SHORT,
    TOKEN_OPT_LONG,
};

struct token
{
    char *argv_opt;
    char *argv_param;
    enum token_type type;
    copt_t *opt;
};

struct tokenizer
{
    struct token *token_arr;
    size_t count;
    size_t alloc;
}; 

int tokenize (struct tokenizer *self, char **argv, size_t argc, copt_t *opt_arr, size_t opt_cnt, void *cb_data);

int add_token (struct tokenizer *self, struct token token);
void destroy_tokenizer (struct tokenizer *self);

copt_t *get_short_option (char character, copt_t *opt_arr, size_t opt_cnt);
copt_t *get_long_option (char *cursor, copt_t *opt_arr, size_t opt_cnt);

/* end of file */