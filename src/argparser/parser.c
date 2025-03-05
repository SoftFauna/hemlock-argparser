
#include "parser.h"

#include "option.h"


/* PUBLIC API */
int 
takes_parameter (copt_type_t type)
{
    switch (type)
    {
    case INPUT_INT:
    case INPUT_STR:
        return 1;
    default:
        return 0;
    }    
}



/* end of file */