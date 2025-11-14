/*
 * Process command line arguments by X Macros
 * Author: TyK <tisyang@gmail.com>
 * License: MIT License
 * Date: 2025-11-14
 *
 * For usage, see example below in comments.
 *
 */

#ifndef _MACRO_ARGS_H
#define _MACRO_ARGS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#define _ARG_STRINGIFY_IMPL(A)   #A
#define _ARG_STRINGIFY(A)   _ARG_STRINGIFY_IMPL(A)
#define _ARG_CONCAT2_IMPL(A, B) A ## B
#define _ARG_CONCAT2(A, B)    _ARG_CONCAT2_IMPL(A, B)
#define _ARG_IF_ELSE_0(THEN, ELSE) ELSE
#define _ARG_IF_ELSE_1(THEN, ELSE) THEN
#define _ARG_IF_ELSE_IMPL(CONDITION, THEN, ELSE)    _ARG_CONCAT2(_ARG_IF_ELSE_, CONDITION)(THEN, ELSE)
#define _ARG_IF_ELSE(CONDITION, THEN, ELSE)         _ARG_IF_ELSE_IMPL(CONDITION, THEN, ELSE)

#define _ARG_IS_ALNUM_CHAR(c)       (((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z') || ((c) >= '0' && (c) <= '9'))
#define _ARG_IS_EMPTY_STR(s)        (sizeof(s) == 1)

#define _ARG_LIT       0
#define _ARG_INT       1
#define _ARG_FLOAT     2
#define _ARG_STR       3
#define _ARG__T(TYPE)       _ARG_##TYPE

#define _ARG__NEED_LIT      0
#define _ARG__NEED_INT      1
#define _ARG__NEED_FLOAT    1
#define _ARG__NEED_STR      1
#define _ARG__NEED(TYPE)    _ARG__NEED_##TYPE

#define _ARG_TYPE_LIT   int
#define _ARG_TYPE_INT   int
#define _ARG_TYPE_FLOAT double
#define _ARG_TYPE_STR   char *

#define _ARG_LIT_FROMSTR(STR, PVAL)     (*(PVAL) = 1, 1)

static inline int _ARG_INT_FROMSTR(const char *STR, _ARG_TYPE_INT *PVAL) {
    char *p = NULL;
    *PVAL = strtol(STR, &p, 10);
    return (*p) == '\0';
}
static inline int _ARG_FLOAT_FROMSTR(const char *STR, _ARG_TYPE_FLOAT *PVAL) {
    char *p = NULL;
    *PVAL = strtod(STR, &p);
    return (*p) == '\0';
}

#define _ARG_STR_FROMSTR(STR, PVAL)     (*(PVAL) = STR, 1)

#define _ARG_FROM_STR(TYPE, STR, PVAL)  _ARG_##TYPE##_FROMSTR(STR, PVAL)

#define _ARG_LIT_FMT    "%d"
#define _ARG_INT_FMT    "%d"
#define _ARG_FLOAT_FMT  "%g"
#define _ARG_STR_FMT    "%s"

#define _ARG_PFMT(TYPE)         _ARG_##TYPE##_FMT

#define _ARG_FIELD_TYPE(TYPE)   _ARG_TYPE_##TYPE
#define ARG_FIELD_NAME(NAME)   arg_##NAME
#define ARG_FIELD_N_NAME(NAME) n_##NAME

#define _ARG_X_STRUCT_FIELD(TYPE, MAXCNT, NAME, SHORT, LONG, HINT, DEF, DESC) \
    _ARG_FIELD_TYPE(TYPE)   ARG_FIELD_NAME(NAME); \
    int ARG_FIELD_N_NAME(NAME);

#define _ARG_X_STRUCT_DEFAULT(TYPE, MAXCNT, NAME, SHORT, LONG, HINT, DEF, DESC) \
    .ARG_FIELD_NAME(NAME) = DEF, \
    .ARG_FIELD_N_NAME(NAME) = 0,

#define ARG_STRUCT_NAME(LIST)  st_##LIST##_name

#define ARG_STRUCT_TYPE(LIST) \
    struct ARG_STRUCT_NAME(LIST) { \
        LIST(_ARG_X_STRUCT_FIELD) \
    }

#define ARG_STRUCT_INITIALIZER(LIST) \
    { LIST(_ARG_X_STRUCT_DEFAULT) }

#define _ARG_HAS_SHORT(SHORT)       _ARG_IS_ALNUM_CHAR(SHORT)
#define _ARG_HAS_HINT(HINT)         (!_ARG_IS_EMPTY_STR(HINT))
#define _ARG_HAS_LONG(LONG)         (!_ARG_IS_EMPTY_STR(LONG))
#define _ARG_CHECK_HINT(TYPE, HINT) ((HINT != NULL) && (_ARG__T(TYPE) || !_ARG_HAS_HINT(HINT)))
#define _ARG_CHECK_SHORT_LONG(SHORT, LONG)  (_ARG_IS_ALNUM_CHAR(SHORT) || _ARG_HAS_LONG(LONG))

#define _ARG_X_STATIC_CHECK(TYPE, MAXCNT, NAME, SHORT, LONG, HINT, DEF, DESC) \
    _Static_assert(_ARG__T(TYPE) >= 0, "Unknown TYPE"); \
    _Static_assert(MAXCNT >= 0, "Maxcount must >= 0"); \
    _Static_assert(LONG != NULL, "Long should not be NULL, use \"\""); \
    _Static_assert(HINT != NULL, "Hint should not be NULL, use \"\""); \
    _Static_assert(!SHORT || _ARG_HAS_SHORT(SHORT), "Short opt char must be alphanumberic or 0"); \
    _Static_assert(_ARG_CHECK_SHORT_LONG(SHORT, LONG), "Short and long cannot all be empty"); \
    _Static_assert(_ARG_CHECK_HINT(TYPE, HINT), "Datahint invalid when TYPE == LIT");

#define _ARG_GEN3STR_SHORT_LONG(SHORT, LONG, SEP)    \
    SHORT ? (char[]){ '-', SHORT, '\0' } : "", (SHORT && _ARG_HAS_LONG(LONG)) ? SEP : "", _ARG_HAS_LONG(LONG) ? "--"LONG : ""


#define _ARG_X_SYNTAX(TYPE, MAXCNT, NAME, SHORT, LONG, HINT, DEF, DESC) \
    printf(" [%s%s%s%s]", _ARG_GEN3STR_SHORT_LONG(SHORT, LONG, "|"), \
           _ARG_HAS_HINT(HINT) ? "="HINT : "");

#define ARG_PRINT_SYNTAX(LIST) \
    LIST(_ARG_X_SYNTAX)

#define _ARG_X_GLOSSARY(TYPE, MAXCNT, NAME, SHORT, LONG, HINT, DEF, DESC) \
    do { \
        int p = printf(" %s%s%s%s", _ARG_GEN3STR_SHORT_LONG(SHORT, LONG, ", "), \
                       _ARG_HAS_HINT(HINT) ? "="HINT : "");\
        if (p < 0) p = 0; p = _arg_preflen - p; if (p < 0) p = 0; \
        printf("%-*s%s\n", p, "", DESC ?: ""); \
    } while (0);

#define ARG_PRINT_GLOSSARY(LIST, PREFLEN) \
    _Static_assert(PREFLEN > 0, "PREFLEN must > 0"); \
    do { \
        int _arg_preflen = PREFLEN; \
        LIST(_ARG_X_GLOSSARY) \
    } while (0);

#define _ARG_X_STRUCT_PRINT(TYPE, MAXCNT, NAME, SHORT, LONG, HINT, DEF, DESC) \
    do { \
        printf(" arg [%d]%s: ", p_arg->ARG_FIELD_N_NAME(NAME), #NAME); \
        printf(_ARG_PFMT(TYPE), p_arg->ARG_FIELD_NAME(NAME)); \
        printf("\t(%s%s%s%s, %s)\n", \
               _ARG_GEN3STR_SHORT_LONG(SHORT, LONG, ", "), \
               _ARG_HAS_HINT(HINT) ? "="HINT : "", \
               DESC ?: ""); \
    } while (0);

#define ARG_STRUCT_PRINT(LIST, STRUCT_P) \
    do { \
        struct ARG_STRUCT_NAME(LIST) *p_arg = STRUCT_P; \
        LIST(_ARG_X_STRUCT_PRINT) \
    } while (0)

#define _ARG_X_PARSE_MATCH(TYPE, MAXCNT, NAME, SHORT, LONG, HINT, DEF, DESC) \
    if (MAXCNT == 0  || p_arg->ARG_FIELD_N_NAME(NAME) < MAXCNT) { \
        _ARG_FIELD_TYPE(TYPE) val; \
        if (_ARG_FROM_STR(TYPE, optarg, &val)) { \
            _ARG_IF_ELSE(_ARG__NEED(TYPE), \
                         p_arg->ARG_FIELD_NAME(NAME) = val, \
                         p_arg->ARG_FIELD_NAME(NAME) += 1); \
                p_arg->ARG_FIELD_N_NAME(NAME) += 1; \
                arg_match = 1; \
        } else { \
            fprintf(stderr, "%s: %s%s%s: invalid argument '%s'\n", \
                    argv[0], _ARG_GEN3STR_SHORT_LONG(SHORT, LONG, ","), \
                    optarg); \
            arg_ret = -1; \
        } \
    } else { \
        fprintf(stderr, "%s: %s%s%s: too many arguments (Max %d)\n", \
                    argv[0], _ARG_GEN3STR_SHORT_LONG(SHORT, LONG, ","), \
                    MAXCNT); \
        arg_ret = -1; \
    }\

#define _ARG_X_PARSE_OPT(TYPE, MAXCNT, NAME, SHORT, LONG, HINT, DEF, DESC) \
    _ARG_IF_ELSE(_ARG__NEED(TYPE), #SHORT ":", #SHORT)

#define _ARG_PARSE_FUNC_NAME(LIST)  _arg_parse_##LIST

#define _ARG_LONG_GEN _ARG_STRINGIFY(_ARG_CONCAT2(__dummy_long_opt_gen_id_, __COUNTER__))

#define _ARG_X_OPTIONS_ITEM(TYPE, MAXCNT, NAME, SHORT, LONG, HINT, DEF, DESC) \
    { _ARG_HAS_LONG(LONG) ? LONG : _ARG_LONG_GEN, _ARG__NEED(TYPE) ? required_argument : no_argument, 0, SHORT },

#define _ARG_X_PARSE_0(TYPE, MAXCNT, NAME, SHORT, LONG, HINT, DEF, DESC) \
    if (strcmp(arg_options[arg_index].name, LONG) == 0) { \
        _ARG_X_PARSE_MATCH(TYPE, MAXCNT, NAME, SHORT, LONG, HINT, DEF, DESC) \
        break; \
    }
#define _ARG_X_PARSE_SHORT(TYPE, MAXCNT, NAME, SHORT, LONG, HINT, DEF, DESC) \
    if (SHORT == arg_c) { \
        _ARG_X_PARSE_MATCH(TYPE, MAXCNT, NAME, SHORT, LONG, HINT, DEF, DESC) \
        break; \
    }

#define _ARG_PARSE_DEFINE(LIST) \
    static int _ARG_PARSE_FUNC_NAME(LIST)(int argc, char *argv[], struct ARG_STRUCT_NAME(LIST) *p_arg) \
    { \
        int arg_ret = 0; \
        int arg_c; \
        optind = 1; \
        char opts[] = LIST(_ARG_X_PARSE_OPT); \
        do { \
            char *src = opts, *dst = opts; \
            while (*src) { \
                if (*src != '\'')   *dst++ = *src; \
                src++; \
            } \
            *dst = '\0'; \
        } while (0); \
        const struct option arg_options[] = { \
            LIST(_ARG_X_OPTIONS_ITEM) \
            { 0, 0, 0 , 0 } \
        }; \
        int arg_index = 0; \
        while ((arg_c = getopt_long(argc, argv, opts, arg_options, &arg_index)) != -1) { \
            int arg_match = 0; \
            if (arg_c == 0) { \
                do { \
                    LIST(_ARG_X_PARSE_0) \
                    arg_ret = -1; \
                } while (0); \
            } \
            do { \
                LIST(_ARG_X_PARSE_SHORT) \
                arg_ret = -1; \
            } while (0); \
            if (arg_ret < 0) break; \
        } \
        return arg_ret ?: optind ; \
    }

#define ARG_PARSE(LIST, ...)    _ARG_PARSE_FUNC_NAME(LIST)(__VA_ARGS__)

#define ARG_DEFINE(LIST) \
    ARG_STRUCT_TYPE(LIST); \
    LIST(_ARG_X_STATIC_CHECK) \
    _ARG_PARSE_DEFINE(LIST)

#define ARG_STRUCT_INIT(LIST, name) \
    struct ARG_STRUCT_NAME(LIST) name = ARG_STRUCT_INITIALIZER(LIST)

/*

// Use Example:

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
    ARG_STRUCT_INIT(APP_ARGS_LIST, args);
    // Before ARG_PARSE, user may change arg fields
    // ret > 0 => optind, < 0 => error!
    int ret = ARG_PARSE(APP_ARGS_LIST, argc, argv, &arg);
    if (ret < 0) {
        return ret;
    }

    if (arg.ARG_FIELD_NAME(print) > 0) {
        printf("optind =%d\n", ret);
        ARG_STRUCT_PRINT(APP_ARGS_LIST, &arg);
        printf("\n");
    }
    if (arg.ARG_FIELD_NAME(help) > 0) {
        printf("Usage: %s", argv[0]);
        ARG_PRINT_SYNTAX(APP_ARGS_LIST);
        printf("\n\nExample:\n");
        ARG_PRINT_GLOSSARY(APP_ARGS_LIST, 30);
        return 0;
    }
    return 0;
}
*/

#endif // _MACRO_ARGS_H
