/* hemlock-argparser - a generic arguement parser written for HEMLOCK.
 * <https://github.com/SoftFauna/hemlock-argparser.git>
 * Copyright (c) 2025 The SoftFauna Team */


#ifndef HEMLOCK_ARGUEMENT_HEADER
#define HEMLOCK_ARGUEMENT_HEADER
#ifdef __cplusplus  /* C++ compatibility */
extern "C" {
#endif
/* code start */


#include <stdbool.h>
#include <stddef.h>

/* handle windows msvc shenanigans */
#if defined _WIN32 || defined __CYGWIN__
#   ifdef LIB_HEMARG_EXPORTS
#       define LIB_HEMARG_API __declspec(dllexport)
#   else
#       define LIB_HEMARG_API __declspec(dllimport)
#   endif
#else
#   ifdef LIB_HEMARG_EXPORTS
#       define LIB_HEMARG_API __attribute__ ((visibility ("default")))
#   else
#       define LIB_HEMARG_API
#   endif
#endif

typedef enum
{
    CONARG_STATUS_ERROR,
    CONARG_STATUS_NA,
    CONARG_STATUS_NO_PARAM,
    CONARG_STATUS_INVALID_PARAM,
    CONARG_STATUS_VALID_PARAM,
} conarg_status_t;

typedef enum
{
    CONARG_ID_ERROR,
    CONARG_ID_UNKNOWN,
    CONARG_ID_PARAM_ERROR,
    CONARG_ID_CUSTOM,
} conarg_id_t;

typedef enum
{
    CONARG_PARAM_NONE,
    CONARG_PARAM_OPTIONAL,
    CONARG_PARAM_REQUIRED,
} conarg_param_t;

typedef struct
{
    int id;
    char *short_name;
    char *long_name;
    conarg_param_t takes_param;
} conarg_t;


#define CONARG_STEP_N_UNSAFE(argc, argv, n) { \
    (argv)+=(n); \
    (argc)-=(n); \
}


#define CONARG_STEP(argc, argv) { \
    (argv)++; \
    (argc)--; \
}


LIB_HEMARG_API int conarg_check (const conarg_t *defs, size_t n, int argc, 
        char **argv, conarg_status_t *status_out);
LIB_HEMARG_API char *conarg_get_param (int argc, char **argv);
LIB_HEMARG_API bool conarg_is_flag (char *arg);


/* code end */
#ifdef __cplusplus  /* C++ compatibility */
}
#endif
#endif /* header guard */
/* end of file */