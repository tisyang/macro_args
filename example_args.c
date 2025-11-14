#include "macro_args.h"

// Define arg list
// TYPE, LIMIT, NAME, SHORT, LONG, HINT, DEFAULT, DESCRIPTION
#define APP_ARGS_LIST(X) \
    ARG_LIT(X, help,      'h', "help",     "show help") \
    ARG_LIT(X, print,     'p', "print",    "print arg struct") \
    ARG_INT(X, verbose,   'v', "verbose",  "<level>", 0,    "verbose level") \
    ARG_NUM(X, timeout,   't', "timeout",  "<secs>",  0.0,  "timeout in secs") \
    ARG_INT(X, longonly,  0,   "longonly", "<flag>",  0,    "test long only arg") \
    ARG_INT(X, shortonly, 's', "",         "<test>",  0,    "test short only arg") \
    ARG_STR(X, from,      'f', "from",     "<file>",  NULL, "file path")

// Generate essential
ARG_DEFINE(APP_ARGS_LIST);

int main(int argc, char **argv)
{
    // Use
    ARG_STRUCT_INIT(APP_ARGS_LIST, arg);
    // Before ARG_PARSE, user may change arg fields
    // ret > 0 => optind, < 0 => error!
    int ret = ARG_PARSE(APP_ARGS_LIST, argc, argv, &arg);
    if (ret < 0) {
        return ret;
    }

    if (arg.arg_print > 0) {
        printf("optind =%d\n", ret);
        ARG_STRUCT_PRINT(APP_ARGS_LIST, &arg);
        printf("\n");
    }
    if (arg.arg_help > 0) {
        printf("Usage: %s", argv[0]);
        ARG_PRINT_SYNTAX(APP_ARGS_LIST);
        printf("\n\nExample:\n");
        ARG_PRINT_GLOSSARY(APP_ARGS_LIST, 30);
        return 0;
    }
    return 0;
}
