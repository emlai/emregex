#include <stdio.h>
#include <assert.h>
#include "ast.h"

reNode reMakeChar(int ch) {
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
        case reSeq:
            printf("(seq");
            for (int idx = 0; idx < node->elemcount; idx++) {
                printf(" ");
                rePrintNode(&node->elems[idx]);
            }
            printf(")");
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
    }
}

void rePrintAST(void) {
    extern reNode root;
    rePrintNode(&root);
}
