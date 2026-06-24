#include "lang/lexer.h"
#include "lang/parser.h"
#include "lang/evaluator.h"

#include <stdio.h>
#include <string.h>

int main() {
    EvalCtx *ctx = ctx_new();

    while (true) {
        char buffer[8192];

        printf("$ ");
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            buffer[strcspn(buffer, "\n")] = '\0';

            Lexer lexer = {
                .src = buffer,
                .pos = 0,
            };
            TokenArray tok_array = lex_all(&lexer);

            Parser parser = {
                .tok_array = tok_array,
                .pos = 0,
            };

            ASTNode *ast = parse_block(&parser);

            RuntimeValue value = eval(ctx, ast);

            free_tok_array(&tok_array);
            if (ast != NULL) {
                parser_free_ast(ast);
            }
        }
    }

    ctx_free(ctx);
}