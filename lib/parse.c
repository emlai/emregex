#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "lex.h"
#include "ast.h"

/// Global storage for the current AST.
reNode root;

static reNode parseToken(int);

static void error(const char* msg) {
    printf("%s\n", msg);
    exit(1);
}

/// Parses a simple postfix node (e.g. '?' or '*') from the input stream
/// and returns it.
static reNode parseNode(reNodeType type) {
    reNode* operand = malloc(sizeof(reNode));
    *operand = root.elems[--root.elemcount];
    reNode node;
    node.type = type;
    node.operand = operand;
    return node;
}

/// Parses a sequence of nodes from the input stream and stores it in the
/// given node. Stops at the given terminator, consuming it.
static void parseSeq(reNode* node, const char terminator) {
    int capacity = 64;
    node->type = reSeq;
    node->elems = malloc(capacity * sizeof(reNode));
    node->elemcount = 0;
    int token;

    while((token = lex()) != terminator) {
        reNode new = parseToken(token); // may decrease node->elemcount
        if (node->elemcount >= capacity) {
            capacity *= 2;
            node->elems = realloc(node->elems, capacity * sizeof(reNode));
        }
        node->elems[node->elemcount++] = new;
    }
}

/// Parses a bracket-delimited range, e.g. [a-z].
static reNode parseRange(void) {
    reNode node;
    node.type = reRange;
    node.lowerbound = lex();
    if (lex() != '-') error("expected '-' after first operand in range");
    node.upperbound = lex();
    if (lex() != reRBracket) error("expected ']' to terminate range");
    return node;
}

/// Parses a node based on the given token, delegating to one of the
/// specialized parser functions above.
static reNode parseToken(int token) {
    switch(token) {
        case '(': {
            reNode node;
            parseSeq(&node, ')');
            return node;
        }
        case '*': return parseNode(reStar);
        case '?': return parseNode(reOpt);
        case reLBracket: return parseRange();
        case reRBracket: assert(0 && "unhandled ]");
        default:  return reMakeChar(token);
    }
}

/// Parses the given regex and stores its AST in the global `root`.
void reParse(const char* regex) {
    lexinit(regex);
    parseSeq(&root, '\0');
}
