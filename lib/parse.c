#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "lex.h"
#include "ast.h"

#define STACKCAPACITY 1024
reNode stack[STACKCAPACITY];
int stacksize;

static inline void push(reNode value) {
    assert(stacksize < STACKCAPACITY && "stack overflow");
    stack[stacksize++] = value;
}

static inline reNode pop(void) {
    assert(stacksize > 0 && "stack underflow");
    return stack[--stacksize];
}

static reNode parseStar(void) {
    reNode* operand = malloc(sizeof(reNode));
    *operand = pop();
    reNode node;
    node.type = reStar;
    node.operand = operand;
    return node;
}

static void parseToken(int token) {
    switch(token) {
        case '*': push(parseStar()); break;
        default: push(reMakeChar(token)); break;
    }
}

void reParse(const char* regex) {
    lexinit(regex);
    int token;
    while((token = lex()) != '\0') {
        parseToken(token);
    }
}
