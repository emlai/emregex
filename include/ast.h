#ifndef EMREGEX_AST_H
#define EMREGEX_AST_H

typedef enum emregexASTNodeType {
    emregexChar,
    emregexStar,
} emregexASTNodeType;

typedef struct emregexASTNode {
    emregexASTNodeType type;
    union {
        struct emregexASTNode* operand;
        char ch;
    };
} emregexASTNode;

emregexASTNode emregexMakeChar(char ch);
void emregexPrintAST(emregexASTNode* nodes, int count);

#endif
