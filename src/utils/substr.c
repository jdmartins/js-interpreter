#include <stdlib.h>
#include <string.h>

/*
* Creates a substring 
* A new string is allocated in the heap
*/
char *substr(const char *source, size_t start, size_t end) {
    //TODO: add bound checks
    size_t source_len = strlen(source);
    int length = ((end - start + 1));  // add one extra space for term char
    char *dest = malloc(length);
    memcpy(dest, &source[start], length);
    dest[length] = '\0';
    return dest;
}