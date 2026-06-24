#include "lexer.h"
#include "parser.h"
#include "evaluator.h"

#include <string.h>

RuntimeValue evaluate(ASTNode *node) {
    if (!node) return val_num(0);

    switch (node->type) {
        case NODE_VALUE_NUMBER: return val_num(node->data.value.num_value);
        case NODE_VALUE_FLOAT: return val_float(node->data.value.float_value);
        case NODE_VALUE_STRING: return val_str(node->data.value.str_value);
    }
}

RuntimeValue val_str(const char *s) {
    RuntimeValue v = { .type = VAL_STR };
    v.str_val = strdup(s);
    return v;
}

void val_free(RuntimeValue *v) {
    if (v && v->type == VAL_STR && v->str_val) {
        free(v->str_val);
        v->str_val = NULL;
    }
}