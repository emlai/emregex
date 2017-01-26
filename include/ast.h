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
        int ch; // a char (< 256) or a reToken (>= 256).
    };
} reNode;

reNode reMakeChar(int ch);
void rePrintAST(void);

#endif
