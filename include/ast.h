#ifndef EMREGEX_AST_H
#define EMREGEX_AST_H

/// The type of a regex node.
typedef enum reNodeType {
    reChar, /// An ASCII character or a token, stored in `ch`.
    reSeq,  /// A sequence of regex nodes, stored in `elems` and `elemcount`.
    reStar, /// A regex star operation, the operand is stored in `operand`.
    reOpt,  /// A regex optional operation ('?'), operand is in `operand`.
    reRange,/// A bracket-delimited range of values, e.g. [a-z], operands in
            /// `lowerbound` and `upperbound`.
} reNodeType;

/// A regex AST node. See above for details on member variables.
typedef struct reNode {
    reNodeType type;
    union {
        struct {
            struct reNode* elems; // the element array when type == reSeq
            int elemcount;
        };
        struct {
            int lowerbound; // the minimum character when type == reRange
            int upperbound; // the maximum character when type == reRange
        };
        struct reNode* operand;
        int ch; // a char (< 256) or a reToken (>= 256).
    };
} reNode;

reNode reMakeChar(int ch);
void rePrintAST(void);

#endif
