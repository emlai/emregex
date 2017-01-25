#ifndef EMREGEX_AST_H
#define EMREGEX_AST_H

typedef enum reNodeType {
    reChar,
    reSeq,
    reStar,
    reOpt,
} reNodeType;

typedef struct reNode {
    reNodeType type;
    union {
        struct {
            struct reNode* elems; // the element array when type == reSeq
            int elemcount;
        };
        struct reNode* operand;
        char ch;
    };
} reNode;

reNode reMakeChar(char ch);
void rePrintAST(void);

#endif
