#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "parser.h"
#include "lexer.h"

typedef enum {
    VAL_NUM,
    VAL_FLOAT,
    VAL_STR,
    VAL_VOID,
} ValueType;

typedef struct {
    ValueType type;
    union {
        int num_val;
        double float_val;
        char *str_val;
    };
} RuntimeValue;

static inline RuntimeValue val_num(int v)      {
    return (RuntimeValue){ .type = VAL_NUM,   .num_val   = v };
}

static inline RuntimeValue val_float(double v) {
    return (RuntimeValue){ .type = VAL_FLOAT, .float_val = v };
}

static inline RuntimeValue val_void()          {
    return (RuntimeValue){ .type = VAL_VOID };
}

RuntimeValue evaluate(ASTNode *node);

#endif