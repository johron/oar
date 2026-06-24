#define OAR_LANG_IMPLEMENTATION
#define OAR_USE_EXTERNAL_FUNCTION_SOURCE

#include "oar.h"

#include <stdio.h>
#include <string.h>

Error* exec_input(EvalCtx *ctx, char* input) {
    Lexer lexer = {
        .src = input,
        .pos = 0,
    };
    TokenArray tok_array = lex_all(&lexer);

    Parser parser = {
        .tok_array = tok_array,
        .pos = 0,
    };

    size_t size = 0;
    size_t cap = 32;
    ASTNode *nodes = malloc(cap * sizeof(ASTNode));

    while (parser.pos < parser.tok_array.size && parser_peek(&parser).type != TOK_EOF && parser_peek(&parser).type != TOK_RBRACE) {
        ASTNode *node = parse_stmt(&parser);
        if (node != NULL) {
            if (size >= cap) {
                cap *= 2;
                nodes = realloc(nodes, cap * sizeof(ASTNode));
            }

            nodes[size++] = *node;
        }
    }

    for (size_t i = 0; i < size; i++) {
        RuntimeValue v;
        Error* err;

        if (eval(ctx, &nodes[i], &v, err) == false) {
            return err;
        }

        parser_free_ast(&nodes[i]);
    }

    free_tok_array(&tok_array);

    return NULL;
}

void repl(EvalCtx *ctx) {
    while (true) {
        char buffer[8192];

        printf("$ ");
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            buffer[strcspn(buffer, "\n")] = '\0';

            Error* err = exec_input(ctx, buffer);
            if (err != NULL) {
                fprintf(stderr, "oar: %s: %s\n", err->type, err->message);
            }
        }
    }
}

RuntimeFunc env_get_func_external(Env *env, const char *name) {
    // Try to spawn `name` as program from path...

    return NULL;
}

int main() {
    EvalCtx *ctx = ctx_new(env_get_func_external);

    repl(ctx);
    
    ctx_free(ctx);
}