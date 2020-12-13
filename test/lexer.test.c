#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "../src/array.utils.c"
#include "../src/lexer.c"
#include "../src/token.c"

void ps(const char *str, ...) {
    va_list arg;

    va_start(arg, str);

    while (str) {
        puts(str);
        str = va_arg(arg, const char *);
    }

    va_end(arg);
}

void fail(char msg[]) {
    printf("❌ %s\n", msg);
    exit(1);
}

void pass(char *msg) {
    printf("✅ %s\n", msg);
}

void test_next_token() {
    char input[] = "=+(){},;";

    const int arr_size = 9;
    token_type expected_tokens[arr_size] = {ASSIGN, PLUS, LPAREN, RPAREN, LBRACE, RBRACE, COMMA, SEMICOLON, EOF};

    // Token out = new (input);
    for (int i = 0; i < arr_size; i++) {
        printf("index: %d\n", i);
        char expected_token = *token_chars[expected_tokens[i]];
        if (expected_token != input[i]) {
            char msg[100];
            fail(snprintf(msg, 50, "Expected: : %c\n Received: %c\n", expected_token, input[i]));
        }
    }

    // pass(sprintf(__func__, "bla"));
}
