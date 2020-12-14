#undef EOF

#include "../lib/tidwall/hashmap.c/hashmap.h"

typedef int token_type;
typedef struct token {
    token_type type;
    char *literal;
} token;

struct keyword {
    char *token;
    token_type type;
};

// Keep a reference to keywords hashmap
// to prevent allocation on every call
static const struct hashmap *kw = NULL;

static int hash_compare(const void *a, const void *b, void *udata) {
    const struct keyword *ua = a;
    const struct keyword *ub = b;

    return strcmp(ua->token, ub->token);
}

static uint64_t hashing(const void *item, uint64_t seed0, uint64_t seed1) {
    const struct keyword *itm = item;
    return hashmap_sip(itm->token, strlen(itm->token), seed0, seed1);
}

struct hashmap *keywords() {
    if (kw == NULL) {
        struct hashmap *kw = hashmap_new(sizeof(struct keyword), 0, 0, 0, hashing, hash_compare, NULL);
        hashmap_set(kw, &(struct keyword){.token = "function", .type = FUNCTION});
        hashmap_set(kw, &(struct keyword){.token = "let", .type = LET});
    }

    return kw;
}

token_type *lookup_ident(char *ident) {
    struct keyword *found = hashmap_get(kw, &(struct keyword){.token = ident});
    if (found != NULL) {
        return found->type;
    }

    return IDENT;
}

/*
*  Token Values in HEX
*/
enum token_type {
    ILLEGAL,
    EOF,

    // --- Identifiers + literals ---
    IDENT,  // add, x, y
    INT,    // decimals

    // --- Operators ---
    ASSIGN,          // =
    PLUS,            // +
    MINUS,           // -
    MULTIPLICATION,  // *

    // --- Delimiters ---
    COMMA,      // ,
    SEMICOLON,  // ;

    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,

    // --- Keywords ---
    FUNCTION,
    LET,
    CONST,
    VAR,
};

const char *token_chars[16] = {
    "ILLEGAL",
    "EOF",
    "IDENT",
    "INT",
    "=",
    "+",
    "-",
    "*",
    ",",
    ";",
    "(",
    ")",
    "{",
    "}",
    "FUNCTION",
    "LET"};
