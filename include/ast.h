#ifndef EMREGEX_AST_H
#define EMREGEX_AST_H

typedef enum reNodeType {
    reChar,
    reStar,
} reNodeType;

typedef struct reNode {
    reNodeType type;
    union {
        struct reNode* operand;
        char ch;
    };
} reNode;

reNode reMakeChar(char ch);
void rePrintAST(reNode* nodes, int count);

#endif
