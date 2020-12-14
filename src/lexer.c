#include <ctype.h>
#include <stdbool.h>

#include "token.c"

typedef struct lexer {
    char *input;        // pointer to an input string
    int position;       // current position in input (points to current char)
    int read_position;  // current reading position in input (after current char)
    char ch;            // current char under examination
} lexer;

lexer *lex_new(char *input) {
    lexer *lex = malloc(sizeof(lexer));
    lex->input = input;
    read_char(lex);
    return lex;
}

static void read_char(lexer *l) {
    // if we reached the end set current char to 0->NULL
    if (l->read_position >= strlen(l->input)) {
        l->ch = 0;
    } else {
        // otherwise store the char at pos
        l->ch = l->input[l->read_position];
    }

    l->position = l->read_position;
    l->read_position += 1;
}

static void skip_whitespace(lexer *l) {
    while (l->ch == ' ' || l->ch == '\t' || l->ch == '\n' || l->ch == '\r') {
        readChar(l);
    }
}

token *next_token(lexer *l) {
    token *tok;

    switch (l->ch) {
        case '=':
            tok = new_token(ASSIGN, l->ch);
        case ';':
            tok = new_token(SEMICOLON, l->ch);
        case '(':
            tok = new_token(LPAREN, l->ch);
        case ')':
            tok = new_token(RPAREN, l->ch);
        case ',':
            tok = new_token(COMMA, l->ch);
        case '+':
            tok = new_token(PLUS, l->ch);
        case '{':
            tok = new_token(LBRACE, l->ch);
        case '}':
            tok = new_token(RBRACE, l->ch);
        case 0:
            tok = new_token(EOF, "");
    }

    return tok;
}


token *token_new(token_type type, char *ch) {
    token *tok = malloc(sizeof(token));
    tok->type = type;
    tok->literal = ch;
    return tok;
}

bool is_letter_or_underscore(char *ch) {
    return isalpha(*ch) || *ch == '_';
}

bool is_digit(char *ch) {
    return isnumber(*ch);
}

void lex_free(lexer *l) {
    free(l);
}