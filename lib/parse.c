#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "lex.h"
#include "ast.h"

#define STACKCAPACITY 1024
emregexASTNode stack[STACKCAPACITY];
int stacksize;

static inline void push(emregexASTNode value) {
    assert(stacksize < STACKCAPACITY && "stack overflow");
    stack[stacksize++] = value;
}

static inline emregexASTNode pop(void) {
    assert(stacksize > 0 && "stack underflow");
    return stack[--stacksize];
}

static emregexASTNode parseStar(void) {
    emregexASTNode* operand = malloc(sizeof(emregexASTNode));
    *operand = pop();
    emregexASTNode node;
    node.type = emregexStar;
    node.operand = operand;
    return node;
}

static void parseToken(int token) {
    switch(token) {
        case '*': push(parseStar()); break;
        default: push(emregexMakeChar(token)); break;
    }
}

void parse(const char* regex) {
    lexinit(regex);
    int token;
    while((token = lex()) != '\0') {
        parseToken(token);
    }
}
