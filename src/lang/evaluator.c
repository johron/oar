#include "lexer.h"
#include "parser.h"
#include "evaluator.h"

RuntimeValue evaluate(ASTNode *node) {
    if (!node) return val_num(0);

    switch (node->type) {
        case NODE_VALUE_NUMBER: return val_num(node->data.value.num_value);

    }
}