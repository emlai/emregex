#include <stdio.h>

static inline int readchar(void) {
    return getc(stdin);
}

static inline void unreadchar(int ch) {
    ungetc(ch, stdin);
}

int lex(void) {
    return readchar();
}
