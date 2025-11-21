/*
 * Process command line arguments by X Macros
 * Author: TyK <tisyang@gmail.com>
 * License: MIT License
 * Date: 2025-11-14
 *
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

#define _ARG__LIT       0
#define _ARG__INT       1
#define _ARG__NUM       2
#define _ARG__STR       3
#define _ARG__T(TYPE)       _ARG__##TYPE

#define _ARG__NEED_LIT      0
#define _ARG__NEED_INT      1
#define _ARG__NEED_NUM      1
#define _ARG__NEED_STR      1
#define _ARG__NEED(TYPE)    _ARG__NEED_##TYPE

#define _ARG_TYPE_LIT   int
#define _ARG_TYPE_INT   int
#define _ARG_TYPE_NUM   double
#define _ARG_TYPE_STR   char *

#define _ARG_LIT_FROMSTR(STR, PVAL)     (*(PVAL) = 1, 1)

static inline int _ARG_INT_FROMSTR(const char *STR, _ARG_TYPE_INT *PVAL) {
    char *p = NULL;
    *PVAL = strtol(STR, &p, 10);
    return (*p) == '\0';
}
static inline int _ARG_NUM_FROMSTR(const char *STR, _ARG_TYPE_NUM *PVAL) {
    char *p = NULL;
    *PVAL = strtod(STR, &p);
    return (*p) == '\0';
}

#define _ARG_STR_FROMSTR(STR, PVAL)     (*(PVAL) = STR, 1)

#define _ARG_FROM_STR(TYPE, STR, PVAL)  _ARG_##TYPE##_FROMSTR(STR, PVAL)

#define _ARG_LIT_FMT    "%d"
#define _ARG_INT_FMT    "%d"
#define _ARG_NUM_FMT    "%g"
#define _ARG_STR_FMT    "%s"

#define _ARG_PFMT(TYPE)         _ARG_##TYPE##_FMT

#define _ARG_FIELD_TYPE(TYPE)   _ARG_TYPE_##TYPE
#define ARG_FIELD_NAME(NAME)    arg_##NAME
#define ARG_FIELD_N_NAME(NAME)  n_##NAME

#define _ARG_REPEAT_1(M)    M
#define _ARG_REPEAT_2(M)    M, _ARG_REPEAT_1(M)
#define _ARG_REPEAT_3(M)    M, _ARG_REPEAT_2(M)
#define _ARG_REPEAT_4(M)    M, _ARG_REPEAT_3(M)
#define _ARG_REPEAT_5(M)    M, _ARG_REPEAT_4(M)
#define _ARG_REPEAT_6(M)    M, _ARG_REPEAT_5(M)
#define _ARG_REPEAT_7(M)    M, _ARG_REPEAT_6(M)
#define _ARG_REPEAT_8(M)    M, _ARG_REPEAT_7(M)
#define _ARG_REPEAT_9(M)    M, _ARG_REPEAT_8(M)
#define _ARG_REPEAT_10(M)   M, _ARG_REPEAT_9(M)
#define _ARG_REPEAT_11(M)   M, _ARG_REPEAT_10(M)
#define _ARG_REPEAT_12(M)   M, _ARG_REPEAT_11(M)
#define _ARG_REPEAT_13(M)   M, _ARG_REPEAT_12(M)
#define _ARG_REPEAT_14(M)   M, _ARG_REPEAT_13(M)
#define _ARG_REPEAT_15(M)   M, _ARG_REPEAT_14(M)
#define _ARG_REPEAT_16(M)   M, _ARG_REPEAT_15(M)
#define _ARG_REPEAT_17(M)   M, _ARG_REPEAT_16(M)
#define _ARG_REPEAT_18(M)   M, _ARG_REPEAT_17(M)
#define _ARG_REPEAT_19(M)   M, _ARG_REPEAT_18(M)
#define _ARG_REPEAT_20(M)   M, _ARG_REPEAT_19(M)
#define _ARG_REPEAT_21(M)   M, _ARG_REPEAT_20(M)
#define _ARG_REPEAT_22(M)   M, _ARG_REPEAT_21(M)
#define _ARG_REPEAT_23(M)   M, _ARG_REPEAT_22(M)
#define _ARG_REPEAT_24(M)   M, _ARG_REPEAT_23(M)
#define _ARG_REPEAT_25(M)   M, _ARG_REPEAT_24(M)
#define _ARG_REPEAT_26(M)   M, _ARG_REPEAT_25(M)
#define _ARG_REPEAT_27(M)   M, _ARG_REPEAT_26(M)
#define _ARG_REPEAT_28(M)   M, _ARG_REPEAT_27(M)
#define _ARG_REPEAT_29(M)   M, _ARG_REPEAT_28(M)
#define _ARG_REPEAT_30(M)   M, _ARG_REPEAT_29(M)
#define _ARG_REPEAT_31(M)   M, _ARG_REPEAT_30(M)
#define _ARG_REPEAT_32(M)   M, _ARG_REPEAT_31(M)
#define _ARG_REPEAT_0(M)    _ARG_REPEAT_32(M)
#define _ARG_MAXCNT_DEF     32
#define _ARG_REPEAT(N, M)   _ARG_CONCAT2(_ARG_REPEAT_, N)(M)
#define _ARG_BRACES(...)    { __VA_ARGS__ }

#define _ARG_X_STRUCT_FIELD(TYPE, MAXCNT, NAME, SHORT, LONG, HINT, DEF, DESC) \
    int ARG_FIELD_N_NAME(NAME); \
    _ARG_IF_ELSE(_ARG__NEED(TYPE), \
                 _ARG_FIELD_TYPE(TYPE) ARG_FIELD_NAME(NAME)[MAXCNT], );

#define _ARG_DO_INIT_ARRAY(NAME, MAXCNT, DEF) \
    .ARG_FIELD_NAME(NAME) = _ARG_BRACES(_ARG_REPEAT(MAXCNT, DEF)),
#define _ARG_DO_INIT_ZERO(NAME, MAXCNT, DEF)

#define _ARG_X_STRUCT_DEFAULT(TYPE, MAXCNT, NAME, SHORT, LONG, HINT, DEF, DESC) \
    .ARG_FIELD_N_NAME(NAME) = 0, \
    _ARG_IF_ELSE(_ARG__NEED(TYPE), \
                 _ARG_DO_INIT_ARRAY, \
                 _ARG_DO_INIT_ZERO)(NAME, MAXCNT, DEF)

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
    _Static_assert(!_ARG__NEED(TYPE) || (MAXCNT >= 1 && MAXCNT <= _ARG_MAXCNT_DEF), "Maxcount must >= 1 and <= 32"); \
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
        if (p < 0) { p = 0; } p = _arg_preflen - p; if (p < 0) { p = 0; } \
        printf("%-*s%s\n", p, "", DESC ?: ""); \
    } while (0);

#define ARG_PRINT_GLOSSARY(LIST, PREFLEN) \
    _Static_assert(PREFLEN > 0, "PREFLEN must > 0"); \
    do { \
        int _arg_preflen = PREFLEN; \
        LIST(_ARG_X_GLOSSARY) \
    } while (0);

#define _ARG__DO_PRINT_NEED(TYPE, NAME) \
    for (int i = 0; i < p_arg->ARG_FIELD_N_NAME(NAME); i++) { \
        if (i) { printf(", "); } else { printf("\n    "); } \
        printf(_ARG_PFMT(TYPE), p_arg->ARG_FIELD_NAME(NAME)[i]); \
    } \
    printf("\n")

#define _ARG__DO_PRINT_NONEED(TYPE, NAME) \
    printf("\n")

#define _ARG_X_STRUCT_PRINT(TYPE, MAXCNT, NAME, SHORT, LONG, HINT, DEF, DESC) \
    do { \
        printf(" arg %s(%s%s%s%s, %s): [%d%s]", \
               #NAME, _ARG_GEN3STR_SHORT_LONG(SHORT, LONG, ", "), \
               _ARG_HAS_HINT(HINT) ? "="HINT : "", DESC ?: "", \
               p_arg->ARG_FIELD_N_NAME(NAME), _ARG_IF_ELSE(_ARG__NEED(TYPE), "/" #MAXCNT, "")); \
        _ARG_IF_ELSE(_ARG__NEED(TYPE), _ARG__DO_PRINT_NEED, _ARG__DO_PRINT_NONEED)(TYPE, NAME); \
    } while (0);

#define ARG_STRUCT_PRINT(LIST, STRUCT_P) \
    do { \
        struct ARG_STRUCT_NAME(LIST) *p_arg = STRUCT_P; \
        LIST(_ARG_X_STRUCT_PRINT) \
    } while (0)

#define _ARG_X_PARSE_MATCH(TYPE, MAXCNT, NAME, SHORT, LONG, HINT, DEF, DESC) \
    if (p_arg->ARG_FIELD_N_NAME(NAME) < MAXCNT) { \
        _ARG_FIELD_TYPE(TYPE) val; \
        if (_ARG_FROM_STR(TYPE, optarg, &val)) { \
            _ARG_IF_ELSE(_ARG__NEED(TYPE), \
                         p_arg->ARG_FIELD_NAME(NAME)[p_arg->ARG_FIELD_N_NAME(NAME)] = val, \
                         ;); \
                p_arg->ARG_FIELD_N_NAME(NAME) += 1; \
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


#define ARG_LIT_N(N, X, NAME, SHORT, LONG, DESC) \
    X(LIT, N, NAME, SHORT, LONG, "", 0, DESC)
#define ARG_INT_N(N, X, NAME, SHORT, LONG, HINT, DEF, DESC) \
    X(INT, N, NAME, SHORT, LONG, HINT, DEF, DESC)
#define ARG_NUM_N(N, X, NAME, SHORT, LONG, HINT, DEF, DESC) \
    X(NUM, N, NAME, SHORT, LONG, HINT, DEF, DESC)
#define ARG_STR_N(N, X, NAME, SHORT, LONG, HINT, DEF, DESC) \
    X(STR, N, NAME, SHORT, LONG, HINT, DEF, DESC)

#define ARG_LIT1(X, NAME, SHORT, LONG, DESC) \
    ARG_LIT_N(1, X, NAME, SHORT, LONG, DESC)
#define ARG_INT1(X, NAME, SHORT, LONG, HINT, DEF, DESC) \
    ARG_INT_N(1, X, NAME, SHORT, LONG, HINT, DEF, DESC)
#define ARG_NUM1(X, NAME, SHORT, LONG, HINT, DEF, DESC) \
    ARG_NUM_N(1, X, NAME, SHORT, LONG, HINT, DEF, DESC)
#define ARG_STR1(X, NAME, SHORT, LONG, HINT, DEF, DESC) \
    ARG_STR_N(1, X, NAME, SHORT, LONG, HINT, DEF, DESC)

#define ARG_LITX(X, NAME, SHORT, LONG, DESC) \
    ARG_LIT_N(256, X, NAME, SHORT, LONG, DESC)
#define ARG_INTX(X, NAME, SHORT, LONG, HINT, DEF, DESC) \
    ARG_INT_N(_ARG_MAXCNT_DEF, X, NAME, SHORT, LONG, HINT, DEF, DESC)
#define ARG_NUMX(X, NAME, SHORT, LONG, HINT, DEF, DESC) \
    ARG_NUM_N(_ARG_MAXCNT_DEF, X, NAME, SHORT, LONG, HINT, DEF, DESC)
#define ARG_STRX(X, NAME, SHORT, LONG, HINT, DEF, DESC) \
    ARG_STR_N(_ARG_MAXCNT_DEF, X, NAME, SHORT, LONG, HINT, DEF, DESC)

#endif // _MACRO_ARGS_H

