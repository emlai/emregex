#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "lex.h"

/// The start of the lexer input string.
static const char* lexinput;

/// The current position in the lexer input string.
static const char* lexinputcurrent;

/// Reads and returns the next character from the input source,
/// advancing the input read position by one as a side-effect.
static inline int readchar(void) {
    return *lexinputcurrent++;
}

/// Moves the input read position back by one character.
/// This shouldn't be called when the input position is at the start.
static inline void unreadchar(void) {
    assert(lexinputcurrent > lexinput);
    lexinputcurrent--;
}

/// Initializes the lexer to read from the given null-terminated character array.
void lexinit(const char* input) {
    lexinput = lexinputcurrent = input;
}

/// Returns the next token scanned from the input stream,
/// advancing the input read position as a side-effect.
int lex(void) {
    const int ch = readchar();
    switch (ch) {
        case '.': return reDot;
        case '\\': {
            const int nextch = readchar();
            switch (nextch) {
                case '.': return '.';
                case 'd': return reDigit;
                case 'D': return reNonDigit;
                default:
                    printf("invalid escape sequence '\\%c'", nextch);
                    exit(1);
            }
            break;
       }
    }
    return ch;
}
