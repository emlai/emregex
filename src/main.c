#include <stdio.h>
#include "parse.h"
#include "ast.h"

extern emregexASTNode stack[];
extern int stacksize;

int main(void) {
    parse();
    emregexPrintAST(stack, stacksize);
    printf("\n");
}
