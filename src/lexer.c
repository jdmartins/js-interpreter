#include <ctype.h>
#include <stdbool.h>

#include "./utils/substr.c"
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

    skip_whitespace(l);

    switch (l->ch) {
        case '=':
            tok = token_new(ASSIGN, l->ch);
        case ';':
            tok = token_new(SEMICOLON, l->ch);
        case '(':
            tok = token_new(LPAREN, l->ch);
        case ')':
            tok = token_new(RPAREN, l->ch);
        case ',':
            tok = token_new(COMMA, l->ch);
        case '+':
            tok = token_new(PLUS, l->ch);
        case '{':
            tok = token_new(LBRACE, l->ch);
        case '}':
            tok = token_new(RBRACE, l->ch);
        case 0:
            tok = token_new(EOF, "");
        default:
            if (is_letter_or_underscore(l->ch)) {
                tok->literal = read_identifier(l);
                tok->type = lookup_ident(tok->literal);
                return tok;
            } else if (is_digit(l->ch)) {
                tok->type = INT;
                tok->literal = read_number(l);
                return tok;
            } else {
                tok = token_new(ILLEGAL, l->ch);
            }
    }

    return tok;
}

// TODO: since read_* fn's do virtually the same
// merge them into one main `read` fn
// and pass as an argument the apropriate
// function for the condition
static char *read_number(lexer *l) {
    int pos = l->position;
    while (is_digit(l->ch)) {
        read_char(l);
    }
    const char *curr_literal = substr(l->input, pos, l->position);
    return curr_literal;
    // TODO: free *curr_literal when its processing is not needed
}

static char *read_identifier(lexer *l) {
    int pos = l->position;
    // update position until the end of the word is found
    while (is_letter_or_underscore(l->ch)) {
        read_char(l);
    }

    const char *curr_literal = substr(l->input, pos, l->position);
    return curr_literal;
    // TODO: free *curr_literal when its processing is not needed
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