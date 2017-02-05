#ifndef EMREGEX_LEX_H
#define EMREGEX_LEX_H

/// A regex token. ASCII characters occupy the values below 256,
/// special regex symbols such as '.' and '$' occupy the values
/// starting from 256.
typedef enum reToken {
    reDot = 256,
    reDigit,
} reToken;

void lexinit(const char* input);
int lex(void);

#endif
