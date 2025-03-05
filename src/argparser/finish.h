
#pragma once

#include "option.h"
#include "tokenizer.h"

#include <stddef.h>


int to_int (char *int_string);
int finish (struct tokenizer *self, copt_t *opt_arr, size_t opt_cnt, void *cb_data);


/* end of file */