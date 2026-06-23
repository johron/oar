#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

#include <stdlib.h>

typedef struct {
    const TokenArray* tok_array;
    size_t pos;
} Parser;

typedef enum {
    NODE_VALUE_NUMBER,
    NODE_VALUE_STRING,
    NODE_VALUE_IDENT,
    NODE_BINARY_OP,
} NodeType;

typedef struct ASTNode ASTNode;

struct ASTNode {
    NodeType type;
    union {
        struct {
            int number_value;
            char* str_value;
            char* ident_value;
        } value;
        struct {
            char op;
            ASTNode *left;
            ASTNode *right;
        } binary_op;
    } data;
};

ASTNode* parse_all(Parser *l);
void free_ast(ASTNode *node);

#endif