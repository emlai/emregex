#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "lex.h"
#include "ast.h"

reNode root;

static reNode parseToken(int);

static reNode parseNode(reNodeType type) {
    reNode* operand = malloc(sizeof(reNode));
    *operand = root.elems[--root.elemcount];
    reNode node;
    node.type = type;
    node.operand = operand;
    return node;
}

static void parseSeq(reNode* node, const char terminator) {
    int capacity = 64;
    node->type = reSeq;
    node->elems = malloc(capacity * sizeof(reNode));
    node->elemcount = 0;
    int token;

    while((token = lex()) != terminator) {
        reNode new = parseToken(token); // may decrease node->elemcount
        if (node->elemcount >= capacity) {
            capacity *= 2;
            node->elems = realloc(node->elems, capacity * sizeof(reNode));
        }
        node->elems[node->elemcount++] = new;
    }
}

static reNode parseToken(int token) {
    switch(token) {
        case '(': {
            reNode node;
            parseSeq(&node, ')');
            return node;
        }
        case '*': return parseNode(reStar);
        case '?': return parseNode(reOpt);
        default:  return reMakeChar(token);
    }
}

void reParse(const char* regex) {
    lexinit(regex);
    parseSeq(&root, '\0');
}
