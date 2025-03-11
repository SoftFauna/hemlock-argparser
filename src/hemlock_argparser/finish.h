/* hemlock-argparser - a generic arguement parser written for HEMLOCK.
 * <https://github.com/SoftFauna/hemlock-argparser.git>
 * Copyright (c) 2025 The SoftFauna Team
 * MIT License */

#ifndef HMARG_FINISH_HEADER
#define HMARG_FINISH_HEADER
#ifdef __cplusplus
extern "C" {
#endif
 

#include "option.h"
#include "tokenizer.h"

#include <stddef.h>


int to_int (char *int_string);
int finish (struct tokenizer *self);



#ifdef __clplusplus
}
#endif /* C++ compat */
#endif /* header guard */
/* end of file */
