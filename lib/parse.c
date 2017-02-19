#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "lex.h"
#include "ast.h"
#include "dynarray.h"

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
    *operand = reDynArrayPop(root.elems);
    reNode node;
    node.type = type;
    node.operand = operand;
    return node;
}

/// Parses a sequence of nodes from the input stream and stores it in the
/// given node. Stops at the given terminator, consuming it.
static void parseSeq(reNode* node, const char terminator) {
    node->type = reSeq;
    reDynArrayInitWithCapacity(64, node->elems);
    int token;

    while((token = lex()) != terminator) {
        reNode new = parseToken(token); // may decrease node->elems.count
        reDynArrayPush(new, node->elems);
    }
}

reDefineDynArrayOf(char);

/// Parses a bracket-delimited range, e.g. [a-z] or [abc].
static reNode parseRange(void) {
    reNode node;

    int ch = lex();
    if (ch == '^') {
        // Negated range, e.g. [^abc].
        node.negated = true;
        node.lowerbound = lex();
    } else {
        node.negated = false;
        node.lowerbound = ch;
    }

    ch = lex();
    if (ch == '-') {
        // Contiguous range expressed with a hyphen, e.g. [a-z].
        node.type = reRange;
        node.upperbound = lex();
        if (lex() != reRBracket) error("expected ']' to terminate range");
    } else {
        // Range of explicitly listed alternatives, e.g. [aeiou].
        node.type = reRange2;
        reDynArray(char) characters;
        reDynArrayInitWithCapacity(16, characters);
        reDynArrayPush(node.lowerbound, characters);

        do {
            reDynArrayPush(ch, characters);
        } while ((ch = lex()) != reRBracket);

        reDynArrayPush('\0', characters);
        node.characters = characters.data;
    }
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
