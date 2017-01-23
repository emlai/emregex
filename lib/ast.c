#include <stdio.h>
#include <assert.h>
#include "ast.h"

reNode reMakeChar(char ch) {
    reNode node;
    node.type = reChar;
    node.ch = ch;
    return node;
}

static void rePrintNode(reNode* node) {
    switch (node->type) {
        case reChar:
            printf("%c", node->ch);
            break;
        case reStar:
            printf("(star ");
            rePrintNode(node->operand);
            printf(")");
            break;
        case reOpt:
            printf("(opt ");
            rePrintNode(node->operand);
            printf(")");
            break;
        default:
            assert(0);
    }
}

void rePrintAST(reNode* node, int count) {
    for (reNode* end = node + count; node != end; node++) {
        rePrintNode(node);
    }
}
