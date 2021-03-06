#include <stdio.h>
#include <assert.h>
#include "ast.h"

/// Helper for making a node out of the given character or token.
reNode reMakeChar(int ch) {
    reNode node;
    node.type = reChar;
    node.ch = ch;
    return node;
}

/// Prints the AST rooted at the given node.
static void rePrintNode(reNode* node) {
    switch (node->type) {
        case reChar:
            printf("%c", node->ch);
            break;
        case reSeq:
            printf("(seq");
            for (int idx = 0; idx < node->elems.count; idx++) {
                printf(" ");
                rePrintNode(&node->elems.data[idx]);
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
        case reRange:
            printf("(range %c %c)", node->lowerbound, node->upperbound);
            break;
        case reRange2:
            printf("(range2 %s)", node->characters);
            break;
    }
}

/// Prints the global AST.
void rePrintAST(void) {
    extern reNode root;
    rePrintNode(&root);
    printf("\n");
}
