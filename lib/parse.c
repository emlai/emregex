#include <stdio.h>
#include "lex.h"

void parse(void) {
    int token;
    while((token = lex()) != EOF) {
        putchar(token);
    }
}
