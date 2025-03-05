
#pragma once 

#include "option.h"
#include "tokenizer.h"


void log_unknown_option (char *argv_opt);
void log_missing_parameter (struct token *p_token);
void log_invalid_parameter_type (struct token *p_token);

char *get_parameter_type_name (copt_type_t type);
char *get_option_name (struct token *p_token);


/* end of file */