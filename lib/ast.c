#include <stdio.h>
#include <assert.h>
#include "ast.h"

emregexASTNode emregexMakeChar(char ch) {
    emregexASTNode node;
    node.type = emregexChar;
    node.ch = ch;
    return node;
}

static void emregexPrintNode(emregexASTNode* node) {
    switch (node->type) {
        case emregexChar:
            printf("%c", node->ch);
            break;
        case emregexStar:
            printf("(star ");
            emregexPrintNode(node->operand);
            printf(")");
            break;
        default:
            assert(0);
    }
}

void emregexPrintAST(emregexASTNode* node, int count) {
    for (emregexASTNode* end = node + count; node != end; node++) {
        emregexPrintNode(node);
    }
}
