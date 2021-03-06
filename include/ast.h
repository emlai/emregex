#ifndef EMREGEX_AST_H
#define EMREGEX_AST_H

#include <stdbool.h>
#include "dynarray.h"

/// The type of a regex node.
typedef enum reNodeType {
    reChar, /// An ASCII character or a token, stored in `ch`.
    reSeq,  /// A sequence of regex nodes, stored in `elems` and `elemcount`.
    reStar, /// A regex star operation, the operand is stored in `operand`.
    reOpt,  /// A regex optional operation ('?'), operand is in `operand`.
    reRange,/// A bracket-delimited range of values, e.g. [a-z], operands in
            /// `lowerbound` and `upperbound`.
    reRange2,/// A bracket-delimited range of explicitly listed characters, e.g.
            /// [aeiou], the null-terminated character list in `alternatives`.
} reNodeType;

typedef struct reNode reNode;
reDefineDynArrayOf(reNode);

/// A regex AST node. See above for details on member variables.
struct reNode {
    reNodeType type;
    union {
        reDynArray(reNode) elems; // the element array when type == reSeq
        struct {
            union {
                struct {
                    int lowerbound; // the minimum character when type == reRange
                    int upperbound; // the maximum character when type == reRange
                };
                char* characters; // the list of characters when type == reRange2
            };
            bool negated; // whether the range is negated (it has the ^ prefix).
        };
        struct reNode* operand;
        int ch; // a char (< 256) or a reToken (>= 256).
    };
};

reNode reMakeChar(int ch);
void rePrintAST(void);

#endif
