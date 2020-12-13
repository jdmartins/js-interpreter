#include <stdio.h>
#include <stdlib.h>

#include "lexer.test.c"

int main(int argc, char *argv[]) {
    printf("=======================\n");
    printf("==== Running tests ====\n");
    printf("=======================\n\n");

    test_next_token();

    return EXIT_SUCCESS;
}