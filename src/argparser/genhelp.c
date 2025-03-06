
#include "debug_trace.h"
#include "log.h"
#include "option.h"
#include "parser.h"

#include <assert.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static float calculate_mean (int *arr, size_t n);
static float *calculate_standard_deviation (int *arr, size_t n);
static int max_without_outlier (int *arr, size_t n, float filter);
static int snprintf_option (char *buf, size_t n, copt_t *src);


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
snprintf_option (char *buf, size_t n, copt_t *src)
{
    /* "  -s, --long-flag=<parameter>"*/
    const char *fmt_s   = "  -%c";
    const char *fmt_l   = "      %s";
    const char *fmt_sl  = "  -%c, %s";
    const char *fmt_sp  = "  -%c=<%s>";
    const char *fmt_lp  = "      %s=<%s>";
    const char *fmt_slp = "  -%c, %s=<%s>";

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

    if (takes_parameter (src->type))
    {
        mode |= MODE_HAS_PARAM;
        param_name = get_parameter_type_name (src->type);
    }
    if (src->long_opt != NULL)
    {
        mode |= MODE_HAS_LONG;
    }
    if (src->short_opt != 0)
    {
        mode |= MODE_HAS_SHORT;
    }

    switch (mode)
    {
    case MODE_SLP:
        return snprintf (buf, n, fmt_slp, src->short_opt, src->long_opt, param_name);
    case MODE_SL:
        return snprintf (buf, n, fmt_sl, src->short_opt, src->long_opt);
    case MODE_S:
        return snprintf (buf, n, fmt_s, src->short_opt);
    case MODE_SP:
        return snprintf (buf, n, fmt_sp, src->short_opt, param_name);
    case MODE_LP:
        return snprintf (buf, n, fmt_lp, src->long_opt, param_name);
    case MODE_L:
        return snprintf (buf, n, fmt_l, src->long_opt);
    default:
        /* error */
        return 0;
    }
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
        result[i] = snprintf_option (NULL, 0, &arr[i]);
    }

    return result;
}


/* PUBLIC API */
void
genhelp_test (FILE *output, copt_t *opt_arr, size_t opt_cnt)
{
    const float MAX_DEVIATION = 100.0f;
    const int WRAP_WIDTH = 80;

    size_t i = 0;
    int *len_arr = NULL;
    int max_col = 0;
    
    void *tmp = NULL;
    char *buf = NULL;
    size_t buf_n = 0;

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

    TRACE_FN ();
    for (i = 0; i < opt_cnt; i++)
    {
        /* extend buffer if need be */
        if (buf == NULL)
        {
            buf = malloc (len_arr[i] + 1);
            if (buf == NULL) { goto exit; }
            buf_n = len_arr[i];
        }
        while (len_arr[i] >= buf_n)
        {
            tmp = realloc (buf, (buf_n * 2) + 1);
            if (tmp == NULL) { goto exit; }
            buf = tmp;
            buf_n *= 2;
        }

        TRACE_FN ();
        /* print option */
        (void)snprintf_option (buf, (int)buf_n, &opt_arr[i]);
        (void)fprintf (output, "%s", buf);

        print_description ();
    }

exit:
    free (buf);
    buf = NULL;
    buf_n = 0;

    free (len_arr);
    len_arr = NULL;

    return;
}


static int
test (char *buf, size_t n, char *desc, int current_col, int desc_start_col)
{
    const int MAX_COL = 80;
    const int MAX_DESC_START = 40;

    char *buf_iter = buf;
    char *iter = desc;
    int length = 0;
    int rc = 0;

    

    int softwrap_len = 0;

    /* softwrap the first line */
    softwrap_len = softwrap (desc, (MAX_COL - current_col));
    rc = snprintf (buf_iter, n, "%*s%.*s\n", 
            (desc_start_col - current_col), "",
            (softwrap_len), iter);
    if (rc == -1) { return 0; }
    length += rc;

    /* move the buffer iterator along */
    if (buf_iter != NULL)
    {
        buf_iter += length;
    }

    /* softwrap the remaining lines */
    for ()

    


}

static void
print_description (FILE *output, int opt_len, int align_col, const int WRAP_WIDTH)
{
    const int MIN_DESCRIPTION_WIDTH = WRAP_WIDTH / 2;
    const int OPTION_PADDING = 4; /* characters after option */
    const int WRAP_PADDING = 2;   /* indent after description newline */

    int max_col = align_col + 4;
    int desc_width = 0;
    int desc_wrap_width = 0;
    size_t desc_len = 0;

    int align_col = 0;
    int align_wrap_col = 0;

    int printed_n = 0;
    int rc = 0;


    align_col = max_col + OPTION_PADDING;
    align_wrap_col = align_col + WRAP_PADDING;

    desc_width = WRAP_WIDTH - align_col;
    desc_wrap_width = WRAP_WIDTH - align_wrap_col;

        TRACE_FN ();

        /* add padding to first line of description */
        if (opt_len > max_col)
        {
            (void)fprintf (output, "\n");
            (void)fprintf (output, "%*s", align_col, "");
            TRACE_FN ();
        }
        else
        {
            (void)fprintf (output, "%*s", (align_col - len_arr[i]), "");
            TRACE_FN ();
        }

        /* print the description's first line */
        desc_len = strlen (opt_arr[i].desc);
        rc = fprintf (output, "%.*s\n", desc_width, opt_arr[i].desc); 

        TRACE_FN ();
        /* print all trailing description lines */
        for (printed_n = rc; printed_n < desc_len; )
        {
            /* line the print up for the wraped line */
            (void)fprintf (output, "%*s", align_wrap_col, "");

            TRACE_FN ();
            /* print the next section */
            rc = fprintf (output, "%.*s\n", desc_wrap_width, (opt_arr[i].desc + printed_n));
            assert (rc != -1);
            printed_n += rc;
            TRACE_FN ();
        }





/* end of file */