#include "macro_args.h"

// Define arg list
// TYPE, LIMIT, NAME, SHORT, LONG, HINT, DEFAULT, DESCRIPTION
#define APP_ARGS_LIST(X) \
    X(LIT,   0, help,      'h', "help",     "",        0,       "show help") \
    X(LIT,   0, print,     'p', "print",    "",        0,       "print arg struct") \
    X(INT,   0, verbose,   'v', "verbose",  "<level>", 0,       "verbose level") \
    X(FLOAT, 0, timeout,   't', "timeout",  "<secs>",  0.0,     "timeout in secs") \
    X(INT,   0, longonly,  0,   "longonly", "<flag>",  0,       "test long only arg") \
    X(INT,   0, shortonly, 's', "",         "<test>",  0,       "test short only arg") \
    X(STR,   0, from,      'f', "from",     "<file>",  NULL,    "file path")

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
