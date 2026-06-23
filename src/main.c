#include "lang/lexer.h"
#include "lang/parser.h"

#include <stdio.h>

int main() {
    char input[] = "echo(\"test\")";

    Lexer lexer = {
        .src = input,
        .pos = 0,
    };
    TokenArray tok_array = lex_all(&lexer);

    for (size_t i = 0; i < tok_array.size; i++) {
        printf("Token type: %s\n", get_token_type_string(tok_array.data[i].type));
        printf("    value: '%s'\n", tok_array.data[i].value.str_value);
        printf("    value: '%d'\n", tok_array.data[i].value.num_value);
        printf("    value: '%s'\n", tok_array.data[i].value.ident_value);
    }

    Parser parser = {
        .tok_array = &tok_array,
        .pos = 0,
    };

    ASTNode *ast = parse_all(&parser);

    free_array(&tok_array);

    if (ast != NULL) {
        free_ast(ast);
    }
}