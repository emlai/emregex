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
        int capacity = 16;
        char* characters = malloc(capacity);
        int count = 0;
        characters[count++] = node.lowerbound;
        do {
            if (count >= capacity) {
                capacity *= 2;
                characters = realloc(characters, capacity);
            }
            characters[count++] = ch;
        } while ((ch = lex()) != reRBracket);
        characters[count] = '\0';
        node.characters = characters;
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
