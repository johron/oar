#include "lexer.h"

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

const char* get_token_type_string(TokenType type) {
    switch (type) {
        case TOK_STR: return "TOK_STR";
        case TOK_NUM: return "TOK_NUM";
        case TOK_IDENT: return "TOK_IDENT";
        case TOK_PLUS: return "TOK_PLUS";
        case TOK_MINUS: return "TOK_MINUS";
        case TOK_STAR: return "TOK_STAR";
        case TOK_SLASH: return "TOK_SLASH";
        case TOK_PERCENT: return "TOK_PERCENT";
        case TOK_EQUAL: return "TOK_EQUAL";
        case TOK_LESS: return "TOK_LESS";
        case TOK_MORE: return "TOK_MORE";
        case TOK_BANG: return "TOK_BANG";
        case TOK_COMMA: return "TOK_COMMA";
        case TOK_PIPE: return "TOK_PIPE";
        case TOK_DB_EQUAL: return "TOK_DB_EQUAL";
        case TOK_BANG_EQUAL: return "TOK_BANG_EQUAL";
        case TOK_LESS_EQUAL: return "TOK_LESS_EQUAL";
        case TOK_MORE_EQUAL: return "TOK_MORE_EQUAL";
        case TOK_LEFT_PAREN: return "TOK_LEFT_PAREN";
        case TOK_RIGHT_PAREN: return "TOK_RIGHT_PAREN";
        case TOK_LEFT_BRACE: return "TOK_LEFT_BRACE";
        case TOK_RIGHT_BRACE: return "TOK_RIGHT_BRACE";
        case TOK_NEWLINE: return "TOK_NEWLINE";
        case TOK_SEMICOLON: return "TOK_SEMICOLON";
        case TOK_EOF: return "TOK_EOF";
        default: return "Unknown TokenType";
    }
}

char peek(Lexer *l) {
    return l->src[l->pos];
}

char advance(Lexer *l) {
    return l->src[l->pos++];
}

char regress(Lexer *l) {
    if (l->pos == 0) {
        return l->src[l->pos]; // TODO: maybe error?
    } else {
        return l->src[l->pos - 1];
    }
}

void skip_ws(Lexer *l) {
    while (isspace(peek(l)) && peek(l) != '\n') advance(l);
}

Token next_token(Lexer *l) {
    skip_ws(l);

    char c = peek(l);

    if (isdigit(c)) {
        int num = 0;

        while (isdigit(peek(l))) {
            num = num * 10 + (advance(l) - '0');
        }

        return (Token){
            .type = TOK_NUM,
            .value = {
                .num_value = num,
            }
        };
    }


    if (isalpha((unsigned char)c)) {
        size_t cap = 128;
        char *str = malloc(cap);
        size_t i = 0;

        while ((c = peek(l)), isalnum((unsigned char)c)) {
            if (i >= cap) {
                cap *= 2;
                char *next_str = realloc(str, cap);
                if (next_str == NULL) {
                    free(str);
                    fprintf(stderr, "Error: out of memory");
                    exit(1);                    
                }
                str = next_str;
            }
            
            advance(l);
            str[i++] = c;
        }

        str[i] = '\0';

        return (Token){
            .type = TOK_IDENT,
            .value = {
                .ident_value = str,
            }
        };
    }

    if (c == '"') {
        advance(l);
        size_t cap = 128;
        char *str = malloc(cap);
        size_t i = 0;

        while (peek(l) != '"' && peek(l) != '\0') {
            c = advance(l);
            if (i >= cap - 1) {
                cap *= 2;
                char *next_str = realloc(str, cap);
                if (next_str == NULL) {
                    free(str);
                    fprintf(stderr, "Error: out of memory\n");
                    exit(1);                    
                }
                str = next_str;
            }
            
            str[i++] = c;
        }

        str[i] = '\0';

        if (peek(l) == '"') {
            advance(l);
        } else {
            free(str);
            fprintf(stderr, "Error: missing '\"' to close string\n");
            exit(1);
        }

        return (Token){
            .type = TOK_STR,
            .value = {
                .str_value = str,
            }
        };
    }

    advance(l);

    switch (c) {
        case '+': return (Token) { .type = TOK_PLUS };
        case '-': return (Token) { .type = TOK_MINUS };
        case '*': return (Token) { .type = TOK_STAR };
        case '/': return (Token) { .type = TOK_SLASH };
        case '%': return (Token) { .type = TOK_PERCENT };

        case '=': {
            if (peek(l) == '=') {
                advance(l);
                return (Token) {.type = TOK_DB_EQUAL };
            } else {
                return (Token) { .type = TOK_EQUAL };
            }
        };
        case '<': {
            if (peek(l) == '=') {
                advance(l);
                return (Token) {.type = TOK_LESS_EQUAL };
            } else {
                return (Token) { .type = TOK_LESS };
            }
        };
        case '>': {
            if (peek(l) == '=') {
                advance(l);
                return (Token) {.type = TOK_MORE_EQUAL };
            } else {
                return (Token) { .type = TOK_MORE };
            }
        };
        case '!': {
            if (peek(l) == '=') {
                advance(l);
                return (Token) {.type = TOK_BANG_EQUAL };
            } else {
                return (Token) { .type = TOK_BANG };
            }
        };
        
        case ',': return (Token) { .type = TOK_COMMA };
        case '|': return (Token) { .type = TOK_PIPE };

        case '(': return (Token) { .type = TOK_LEFT_PAREN };
        case ')': return (Token) { .type = TOK_RIGHT_PAREN };
        case '{': return (Token) { .type = TOK_LEFT_BRACE };
        case '}': return (Token) { .type = TOK_RIGHT_BRACE };

        case '\n': return (Token){ .type = TOK_NEWLINE };
        case ';': return (Token){ .type = TOK_SEMICOLON };
        case '\0': return (Token){ .type = TOK_EOF };

        default:
            printf("Unknown character: '%c'\n", c);
            exit(1);
    }
}

void init_array(TokenArray *a) {
    a->size = 0;
    a->cap = 32;
    a->data = malloc(a->cap * sizeof(Token));
}

void push_token(TokenArray *a, Token t) {
    if (a->size >= a->cap) {
        a->cap *= 2;
        a->data = realloc(a->data, a->cap * sizeof(Token));
    }

    a->data[a->size++] = t;
}

TokenArray lex_all(Lexer *l) {
    TokenArray arr;
    init_array(&arr);

    while (true) {
        Token t = next_token(l);
        push_token(&arr, t);

        if (t.type == TOK_EOF)
            break;
    }

    return arr;
}

void free_array(TokenArray *a) {
    if (a == NULL) return;

    for (size_t i = 0; i < a->size; i++) {
        switch (a->data[i].type) {
            case TOK_STR: {
                if (a->data[i].value.str_value != NULL) {
                    free(a->data[i].value.str_value);
                    a->data[i].value.str_value = NULL;
                }
                break;
            };
            case TOK_IDENT: {
                if (a->data[i].value.ident_value != NULL) {
                    free(a->data[i].value.ident_value);
                    a->data[i].value.ident_value = NULL;
                }
                break;
            };
            default: {};
            // case TOK_NUM: {}; // This tok has data, but not in heap
        }
    }

    free(a->data);
    a->data = NULL;

    a->size = 0;
    a->cap = 0;
}