/* hemlock-argparser - a generic arguement parser written for HEMLOCK.
 * <https://github.com/SoftFauna/hemlock-argparser.git>
 * Copyright (c) 2025 The SoftFauna Team
 * MIT License */

#ifndef HMARG_LOG_HEADER
#define HMARG_LOG_HEADER
#ifdef __cplusplus
extern "C" {
#endif

#include "option.h"
#include "tokenizer.h"


void log_unknown_short_option (char argv_opt);
void log_unknown_long_option (char *long_opt);
void log_missing_parameter (struct token *p_token);
void log_invalid_parameter_type (struct token *p_token);
void log_useless_parameter (struct token *p_token);

void log_fatal_unknown_type (copt_type_t type);

char *get_parameter_type_name (copt_type_t type);
char *get_option_name (struct token *p_token);


#ifdef __clplusplus
}
#endif /* C++ compat */
#endif /* header guard */
/* end of file */
