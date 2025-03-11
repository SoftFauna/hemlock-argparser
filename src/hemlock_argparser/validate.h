/* hemlock-argparser - a generic arguement parser written for HEMLOCK.
 * <https://github.com/SoftFauna/hemlock-argparser.git>
 * Copyright (c) 2025 The SoftFauna Team
 * MIT License */

#ifndef HMARG_VALIDATE_HEADER
#define HMARG_VALIDATE_HEADER
#ifdef __cplusplus
extern "C" {
#endif

#include "tokenizer.h"


int is_valid_str (char *maybe_str);
int is_valid_int (char *maybe_int);
int validate (struct tokenizer *self);

#ifdef __clplusplus
}
#endif /* C++ compat */
#endif /* header guard */
/* end of file */
