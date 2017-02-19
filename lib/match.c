#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "match.h"
#include "ast.h"
#include "lex.h"
#include "dynarray.h"

/// A specific path in the matcher state graph.
typedef struct reBranch {
    char input;
    const reNode* node;
} reBranch;

extern reNode root;

/// Storage and bookkeeping data for the current set of branches.
reDefineDynArrayOf(reBranch);
static reDynArray(reBranch) branches;
#define get(branch) branches.data[branch]

/// The input stream, a file or the standard input stream.
static FILE* inputfile;

/// Advances the input member of the given branch to the next
/// character read from the input stream.
static inline void advanceInput(int branch) {
    int input = getc(inputfile);
    get(branch).input = (input == EOF || input == '\n') ? '\0' : input;
}

/// Removes the given branch from the branches array.
void killBranch(int branch) {
    reDynArrayRemoveAt(branch, branches);
}

/// Creates a new branch and adds it to the branches array.
/// Only MAX_BRANCHES branches can be in the array at once.
void addBranch(char input, const reNode* node) {
    reDynArrayPush(((reBranch) {input, node}), branches);
}

/// Checks whether the given input symbol matches the token.
static bool inputMatches(const char input, const int token) {
    switch ((reToken) token) {
        case reDot: return true;
        case reDigit: return isdigit(input);
        case reNonDigit: return !isdigit(input);
        case reLBracket: assert(0 && "leftover [");
        case reRBracket: assert(0 && "leftover ]");
    }
    return input == token;
}

/// Checks whether the given input symbol is within the range
/// specified by the (inclusive) lower and upper bounds.
static bool inputMatchesRange(char input, char lowerbound, char upperbound, bool negated) {
    if (negated) return input < lowerbound || input > upperbound;
    return input >= lowerbound && input <= upperbound;
}

/// Checks whether the given input symbol is in the given character array.
static bool inputMatchesRange2(char input, char* characters, bool negated) {
    while (*characters)
        if (*characters++ == input)
            return !negated;
    return negated;
}

/// Evaluates the given node, and returns true if the node
/// should be consumed at the top level (i.e. in branchHasMatch()).
static bool consumeNode(int branch, const reNode* node) {
    switch (node->type) {
        case reChar:
            if (!inputMatches(get(branch).input, node->ch)) {
                killBranch(branch);
            } else {
                advanceInput(branch);
                return true;
            }
            break;
        case reSeq:
            for (int idx = 0; idx < node->elems.count; idx++) {
                if (!consumeNode(branch, &node->elems.data[idx]))
                    return false;
            }
            return true;
        case reStar:
            addBranch(get(branch).input, node + 1);
            consumeNode(branch, node->operand);
            break;
        case reOpt:
            addBranch(get(branch).input, node + 1);
            return consumeNode(branch, node->operand);
        case reRange:
            if (!inputMatchesRange(get(branch).input, node->lowerbound, node->upperbound, node->negated)) {
                killBranch(branch);
            } else {
                advanceInput(branch);
                return true;
            }
            break;
        case reRange2:
            if (!inputMatchesRange2(get(branch).input, node->characters, node->negated)) {
                killBranch(branch);
            } else {
                advanceInput(branch);
                return true;
            }
            break;
    }
    return false;
}

/// Advances the specified branch and returns true if a match
/// has been found in the branch.
bool branchHasMatch(int branch) {
    if (get(branch).node >= root.elems.data + root.elems.count) { // node out of bounds
        if (get(branch).input != '\0') killBranch(branch);
        return get(branch).input == '\0';
    }
    if (consumeNode(branch, get(branch).node)) {
        get(branch).node++; // consume top-level node
    }
    return false;
}

/// Matches the given input stream against the global regex,
/// returning true if input matches the regex.
bool reMatch(FILE* input) {
    inputfile = input;
    addBranch(0, &root.elems.data[0]);
    advanceInput(0);

    while (branches.count > 0) {
        for (int branch = 0; branch < branches.count; branch++) {
            if (branchHasMatch(branch)) {
                return true;
            }
        }
    }
    return false;
}
