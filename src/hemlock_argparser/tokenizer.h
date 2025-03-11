/* hemlock-argparser - a generic arguement parser written for HEMLOCK.
 * <https://github.com/SoftFauna/hemlock-argparser.git>
 * Copyright (c) 2025 The SoftFauna Team
 * MIT License */

#ifndef HMARG_TOKENIZER_HEADER
#define HMARG_TOKENIZER_HEADER
#ifdef __cplusplus
extern "C" {
#endif
 

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

#ifdef __clplusplus
}
#endif /* C++ compat */
#endif /* header guard */
/* end of file */
