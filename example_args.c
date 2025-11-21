#include "macro_args.h"

// 1. Define arg list
// ARG_LIT?(X, token, short opt, long opt, descrption)
// ARG_INT?/ARG_NUM?/ARG_STR*:
// (X, token, short opt, long opt, arg data type hint, default value, description)
// For ARG_TYP1 means only 0 or 1 args input
// For ARG_TYPX means most 32(INTERL LIMIT) args input(For ARG_LITX, Limit is 256)
// For custom count limit, use ARG_TYP_N(N, X...)
#define APP_ARGS_LIST(X) \
    ARG_LITX(X, help,       'h', "help",        "show help") \
    ARG_LIT1(X, print,      'p', "print",       "print arg struct") \
    ARG_LITX(X, verbose,    'v', "verbose",     "verbose") \
    ARG_NUM1(X, timeout,    't', "timeout",     "<secs>",  0.0,  "timeout in secs") \
    ARG_LIT1(X, longonly,   0,   "longonly",    "test long only arg") \
    ARG_LIT1(X, shortonly,  's', "",            "test short only arg") \
    ARG_STR1(X, from,       'f', "from",        "<file>",  "1.txt", "file path") \
    ARG_STRX(X, token,      'k', "token",       "<token>", "token0", "process tokens")

// 2. Generate essential
ARG_DEFINE(APP_ARGS_LIST);

int main(int argc, char **argv)
{
    // 3. Decleare struct to storage parse result
    ARG_STRUCT_INIT(APP_ARGS_LIST, arg);
    // 4. Parse argv with struct
    // ret > 0 => optind, < 0 => error!
    int ret = ARG_PARSE(APP_ARGS_LIST, argc, argv, &arg);
    if (ret < 0) {
        printf("Usage: %s", argv[0]);
        ARG_PRINT_SYNTAX(APP_ARGS_LIST);
        printf("\n");
        return ret;
    }
    // Use struct field to check result
    // For LIT, use n_XXX
    if (arg.n_print > 0) {
        printf("optind =%d\n", ret);
        ARG_STRUCT_PRINT(APP_ARGS_LIST, &arg);
        printf("\n");
    }
    if (arg.n_help > 0) {
        printf("Usage: %s", argv[0]);
        ARG_PRINT_SYNTAX(APP_ARGS_LIST);
        printf("\n\nExample:\n");
        ARG_PRINT_GLOSSARY(APP_ARGS_LIST, 30);
        return 0;
    }
    // For other TYPE, use n_xxx and arg_xxx[] to get values
    if (arg.n_token <= 0) {
        printf("Need token provide\n");
        return -1;
    } else {
        for (int i = 0; i < arg.n_token; i++) {
            printf("token %d: %s\n", i, arg.arg_token[i]);
        }
    }
    // only first of args will be default, other will fill by zero.
    printf("from: %s\n", arg.arg_from[0]);
    return 0;
}
