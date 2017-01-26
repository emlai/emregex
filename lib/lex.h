#ifndef EMREGEX_LEX_H
#define EMREGEX_LEX_H

typedef enum reToken {
    reDot = 256,
} reToken;

void lexinit(const char* input);
int lex(void);

#endif
