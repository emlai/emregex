#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "lex.h"

static const char* lexinput;
static const char* lexinputcurrent;

static inline int readchar(void) {
    return *lexinputcurrent++;
}

static inline void unreadchar(void) {
    assert(lexinputcurrent > lexinput);
    lexinputcurrent--;
}

void lexinit(const char* input) {
    lexinput = lexinputcurrent = input;
}

int lex(void) {
    const int ch = readchar();
    switch (ch) {
        case '.': return reDot;
        case '\\': {
            const int nextch = readchar();
            switch (nextch) {
                case '.': return '.';
                default:
                    printf("invalid escape sequence '\\%c'", nextch);
                    exit(1);
            }
            break;
       }
    }
    return ch;
}
