
#include "genhelp.h"

#include "colors.h"
#include "debug_trace.h"
#include "log.h"
#include "option.h"
#include "parser.h"
#include "pretty.h"

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static float calculate_mean (int *arr, size_t n);
static float *calculate_standard_deviation (int *arr, size_t n);
static int max_without_outlier (int *arr, size_t n, float filter);
static int softwrap (char *src, size_t hard_max);
static int *generate_option_len_array (copt_t *arr, size_t n);

static int snprintf_description (char *buf, size_t buf_n, char *desc, int current_col, int base_col, int wrap_col);
static int csnprintf_option (char *buf, size_t buf_n, int *p_size, int *p_plen, copt_t *src);
static int snprintf_usage (char *buf, size_t buf_n, copt_t *opt_arr, size_t opt_cnt, int wrap_col);




/* PUBLIC API */
char *
gen_help_page (copt_prog_t *prog, int wrap_col)
{
    const char FMT[] = {
        C_LABEL"usage"C_RESET": "C_BINARY"%s"C_RESET" "C_PARAM"<options>"C_RESET"\n"
        "%s\n"
        "\n"
        C_LABEL"options"C_RESET":\n"
        "%s\n"
        "\n"
        C_LABEL"repository"C_RESET": "C_LINK"<%s>"C_RESET"\n"
        C_LABEL"issues"C_RESET": "C_LINK"<%s>"C_RESET"\n"
        C_LABEL"contact"C_RESET": "C_NAME"%s"C_RESET" "C_EMAIL"<%s>"C_RESET"\n"
        "%s\n"
    };


    char  *help = NULL;
    size_t size = 0;

    char *options = NULL;

    TRACE_FN ();

    assert (prog != NULL);
    assert (prog->name != NULL);
    assert (prog->description != NULL);
    assert (prog->repository_url != NULL);
    assert (prog->issues_url != NULL);
    assert (prog->contact_name != NULL);
    assert (prog->contact_email != NULL);

    options = gen_usage (prog->options, prog->option_count, wrap_col);

    size = csnprintf (NULL, 0, FMT, 
            prog->name,
            prog->description,
            options,
            prog->repository_url,
            prog->issues_url,
            prog->contact_name, prog->contact_email,
            (prog->help_extra == NULL) ? "" : prog->help_extra
    );
    help = malloc (size);
    (void)csnprintf (help, size, FMT, 
            prog->name,
            prog->description,
            options,
            prog->repository_url,
            prog->issues_url,
            prog->contact_name, prog->contact_email,
            (prog->help_extra == NULL) ? "" : prog->help_extra
    );
    
    free (options);
    options = NULL;

    return help;
}


char *
gen_version_page (copt_prog_t *prog)
{
    const char FMT[] = {
        C_BINARY"%s"C_RESET" %s\n"
        "Copyright (c) %s %s\n"
        "%s License: "C_LINK"<%s>"C_RESET"\n"
        C_LINK"<%s>"C_RESET"\n"
        "%s\n"
    };


    char  *version = NULL;
    size_t size = 0;

    TRACE_FN ();

    assert (prog != NULL);
    assert (prog->name != NULL);
    assert (prog->version != NULL);
    assert (prog->copyright_year != NULL);
    assert (prog->copyright_holder != NULL);
    assert (prog->license_name != NULL);
    assert (prog->license_url != NULL);
    assert (prog->repository_url != NULL);


    size = csnprintf (NULL, 0, FMT,
        prog->name, prog->version,
        prog->copyright_year, prog->copyright_holder,
        prog->license_name, prog->license_url,
        prog->repository_url,
        (prog->version_extra == NULL) ? "" : prog->version_extra
    );
    version = malloc (size);
    (void)csnprintf (version, size, FMT,
        prog->name, prog->version,
        prog->copyright_year, prog->copyright_holder,
        prog->license_name, prog->license_url,
        prog->repository_url,
        (prog->version_extra == NULL) ? "" : prog->version_extra
    );

    return version;
}


char *
gen_usage (copt_t *opt_arr, size_t opt_cnt, int wrap_col)
{
    size_t size = 0;
    char *usage = NULL;

    TRACE_FN ();

    size = snprintf_usage (NULL, 0, opt_arr, opt_cnt, wrap_col);
    usage = malloc (size);
    (void)snprintf_usage (usage, size, opt_arr, opt_cnt, wrap_col);

    return usage;
}


/* PRIVATG FILE-STATIC */
static float
calculate_mean (int *arr, size_t n)
{
    size_t i = 0;
    int total = 0;
    float mean = 0.0f;

    TRACE_FN ();

    for (i = 0; i < n; i++)
    {
        total += arr[i];
    }

    mean = (float)total / n;

    return mean;
}


static float *
calculate_standard_deviation (int *arr, size_t n)
{
    size_t i = 0;
    float mean = 0.0f;
    float *result = NULL;

    float a = 0.0f;
    float b = 0.0f;

    TRACE_FN ();

    result = malloc (sizeof (float) * n);
    if (result == NULL) { return NULL; }

    mean = calculate_mean (arr, n);

    for (i = 0; i < n; i++)
    {
        a = mean - (float)arr[i];
        b = powf (a, 2);
        result[i] = b;
    }

    return result;
}


static int 
max_without_outlier (int *arr, size_t n, float filter)
{
    size_t i = 0;
    int max = 0;
    float *deviation_arr = NULL;

    TRACE_FN ();

    deviation_arr = calculate_standard_deviation (arr, n);

    for (i = 0; i < n; i++)
    {
        /* skip outliers */
        if (deviation_arr[i] >= filter)
        {
            continue;
        }

        /* check if new max */
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }

    free (deviation_arr);
    deviation_arr = NULL;

    return max;
}


static int
softwrap (char *src, size_t hard_max)
{
    char *iter = 0;
    size_t i = 0;
    size_t length = 0;
    
    TRACE_FN ();

    if (src == NULL) { return 0; }
    
    length = strlen (src);
    if (length <= hard_max)
    {
        return (int)length;
    }
    
    iter = &src[hard_max];
    for (i = hard_max; i > 0; i--)
    {
        if (*iter == ' ')
        {
            return (int)i;
        }

        iter--;
    }

    return (int)hard_max;
}


static int *
generate_option_len_array (copt_t *arr, size_t n)
{
    size_t i = 0;
    int *result = NULL;

    TRACE_FN ();

    result = malloc (sizeof (*result) * n);

    for (i = 0; i < n; i++)
    {
        (void)csnprintf_option (NULL, 0, NULL, &result[i], &arr[i]);
    }

    return result;
}


static int
csnprintf_option (char *buf, size_t buf_n, int *p_size, int *p_plen, copt_t *opt_arr)
{
    const char *fmt_s   = "  "C_OPTION"-%c"C_RESET;
    const char *fmt_l   = "      "C_OPTION"%s"C_RESET;
    const char *fmt_sl  = "  "C_OPTION"-%c"C_RESET", "C_OPTION"%s"C_RESET;
    const char *fmt_sp  = "  "C_OPTION"-%c"C_RESET"="C_PARAM"<%s>"C_RESET;
    const char *fmt_lp  = "      "C_OPTION"%s"C_RESET"="C_PARAM"<%s>"C_RESET;
    const char *fmt_slp = "  "C_OPTION"-%c"C_RESET", "C_OPTION"%s"C_RESET"="C_PARAM"<%s>"C_RESET;

    char *param_name = NULL;
    unsigned mode = 0;

    enum
    {
        MODE_HAS_PARAM = 0x1, /* 0001 */
        MODE_HAS_LONG  = 0x2, /* 0010 */
        MODE_HAS_SHORT = 0x4, /* 0100 */
    };

    enum
    {
        MODE_NONE = 0x0,
        MODE_SLP = (MODE_HAS_SHORT | MODE_HAS_LONG | MODE_HAS_PARAM),
        MODE_SL  = (MODE_HAS_SHORT | MODE_HAS_LONG),
        MODE_S   = (MODE_HAS_SHORT),
        MODE_SP  = (MODE_HAS_SHORT |                 MODE_HAS_PARAM),
        MODE_LP  = (                 MODE_HAS_LONG | MODE_HAS_PARAM),
        MODE_L   = (                 MODE_HAS_LONG),
    };
        
    TRACE_FN ();

    if (takes_parameter (opt_arr->type))
    {
        mode |= MODE_HAS_PARAM;
        param_name = get_parameter_type_name (opt_arr->type);
    }
    if (opt_arr->long_opt != NULL)
    {
        mode |= MODE_HAS_LONG;
    }
    if (opt_arr->short_opt != 0)
    {
        mode |= MODE_HAS_SHORT;
    }

    switch (mode)
    {
    case MODE_SLP:
        return csnprintf_v2 (buf, buf_n, p_size, p_plen, fmt_slp, opt_arr->short_opt, opt_arr->long_opt, param_name);
    case MODE_SL:
        return csnprintf_v2 (buf, buf_n, p_size, p_plen, fmt_sl, opt_arr->short_opt, opt_arr->long_opt);
    case MODE_S:
        return csnprintf_v2 (buf, buf_n, p_size, p_plen, fmt_s, opt_arr->short_opt);
    case MODE_SP:
        return csnprintf_v2 (buf, buf_n, p_size, p_plen, fmt_sp, opt_arr->short_opt, param_name);
    case MODE_LP:
        return csnprintf_v2 (buf, buf_n, p_size, p_plen, fmt_lp, opt_arr->long_opt, param_name);
    case MODE_L:
        return csnprintf_v2 (buf, buf_n, p_size, p_plen, fmt_l, opt_arr->long_opt);
    default:
        /* error */
        *p_plen = 0;
        *p_size = 0;
        return -1;
    }
}


static int
snprintf_description (char *buf, size_t buf_n, char *desc, int current_col, 
                      int base_col, int wrap_col)
{
    const int NEWLINE_INDENT = 2;

    char  *buf_iter      = buf;
    size_t buf_remaining = buf_n;
    size_t total_written = 0;

    int desc_start_col = base_col;

    char  *iter = desc;
    size_t total_read  = 0;
    size_t desc_length = 0; 

    TRACE_FN ();

    desc_length = strlen (desc);

    if (current_col >= desc_start_col)
    {
        total_written++;
        if (buf_iter != NULL) 
        { 
            *buf_iter = '\n'; 
            buf_iter++;
        }
        current_col = 0;
    }

    while (total_read < desc_length)
    {
        int padding_cols   = desc_start_col - current_col;
        int remaining_cols = wrap_col - desc_start_col;

        int print_n_cols = softwrap (iter, remaining_cols);
        int result_n = snprintf (buf_iter, buf_remaining, "%*s%.*s\n", 
                padding_cols, "",
                print_n_cols, iter);

        total_written += result_n;
        total_read    += print_n_cols;
        iter += print_n_cols;

        while (isspace (*iter)) 
        {
            iter++;
            total_read++;
        }

        current_col = 0;

        desc_start_col = base_col + NEWLINE_INDENT;

        if (buf_iter == NULL) { continue; }
        buf_iter += result_n;
        buf_remaining -= result_n;
    }

    return (int)total_written;
}


static int
snprintf_usage (char *buf, size_t buf_n, copt_t *opt_arr, size_t opt_cnt, int wrap_col)
{
    const float MAX_DEVIATION = 100.0f;
    const int POST_OPTION_PADDING = 4;

    size_t i = 0;
    int *len_arr = NULL;
    int max_col = 0;
    
    size_t total = 0;
    int option_size = 0;
    int option_plen = 0;
    int description_size = 0;
    //int description_plen = 0;

    TRACE_FN ();
   
    /* fmt:
     * "  -s, --long                  description.\n"
     * "  -a, --long-extra            description.\n"
     * "  -b, --long-more=<number>    description that is verry verry long and needs to\n"
     * "                                wrap to the next line will look like this.\n"
     * "  -c, --long-test-this-is-verry-long\n
     * "                              description.\n"
     */
    len_arr = generate_option_len_array (opt_arr, opt_cnt);
    max_col = max_without_outlier (len_arr, opt_cnt, (float)MAX_DEVIATION);

    for (i = 0; i < opt_cnt; i++)
    {
        /* get the print options */
        (void)csnprintf_option (buf, buf_n, &option_size, &option_plen, &opt_arr[i]);
        if (buf != NULL)
        {
            buf   += option_size;
            buf_n -= option_size;
        }

        /* and the descriptions */
        description_size = snprintf_description (buf, buf_n, opt_arr[i].desc,
                (int)option_plen, (int)(max_col + POST_OPTION_PADDING), wrap_col);
        if (buf != NULL)
        {
            buf   += description_size;
            buf_n -= description_size;
        }

        /* and update the total */
        total += option_size + description_size;
    }

    free (len_arr);
    len_arr = NULL;
    total++;
    
    return (int)total;
}


/* end of file */
