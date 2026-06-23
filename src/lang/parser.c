#include "lexer.h"
#include "parser.h"

ASTNode* parse_all(Parser *l) {
    return NULL;
}

void free_ast(ASTNode *node) {
    if (!node) return;

    if (node->type == NODE_BINARY_OP) {
        free_ast(node->data.binary_op.left);
        free_ast(node->data.binary_op.right);
    }
    free(node);
}
