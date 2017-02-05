#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "match.h"
#include "ast.h"
#include "lex.h"

/// A specific path in the matcher state graph.
typedef struct reBranch {
    char input;
    const reNode* node;
} reBranch;

extern reNode root;

/// Storage and bookkeeping data for the current set of branches.
#define MAX_BRANCHES 1024
static reBranch branches[MAX_BRANCHES];
static int branchcount = 0;

/// The input stream, a file or the standard input stream.
static FILE* inputfile;

/// Advances the input member of the given branch to the next
/// character read from the input stream.
static inline void advanceInput(reBranch* branch) {
    int input = getc(inputfile);
    branch->input = (input == EOF || input == '\n') ? '\0' : input;
}

/// Removes the given branch from the branches array.
void killBranch(reBranch* branch) {
    assert(branchcount < MAX_BRANCHES);
    // shift elements after this branch
    int count = branchcount - (branch - branches) - 1;
    memmove(branch, branch + 1, count * sizeof(reBranch));
    branchcount--;
}

/// Creates a new branch and adds it to the branches array.
/// Only MAX_BRANCHES branches can be in the array at once.
void addBranch(char input, const reNode* node) {
    assert(branchcount < MAX_BRANCHES);
    branches[branchcount].input = input;
    branches[branchcount].node = node;
    branchcount++;
}

/// Checks whether the given input symbol matches the token.
static bool inputMatches(const char input, const int token) {
    switch ((reToken) token) {
        case reDot: return true;
        case reDigit: return isdigit(input);
    }
    return input == token;
}

/// Evaluates the given node, and returns true if the node
/// should be consumed at the top level (i.e. in branchHasMatch()).
static bool consumeNode(reBranch* branch, const reNode* node) {
    switch (node->type) {
        case reChar:
            if (!inputMatches(branch->input, node->ch)) {
                killBranch(branch);
            } else {
                advanceInput(branch);
                return true;
            }
            break;
        case reSeq:
            for (int idx = 0; idx < node->elemcount; idx++) {
                if (!consumeNode(branch, &node->elems[idx]))
                    return false;
            }
            return true;
        case reStar:
            addBranch(branch->input, node + 1);
            consumeNode(branch, node->operand);
            break;
        case reOpt:
            addBranch(branch->input, node + 1);
            return consumeNode(branch, node->operand);
    }
    return false;
}

/// Advances the specified branch and returns true if a match
/// has been found in the branch.
bool branchHasMatch(reBranch* branch) {
    if (branch->node >= root.elems + root.elemcount) { // node out of bounds
        if (branch->input != '\0') killBranch(branch);
        return branch->input == '\0';
    }
    if (consumeNode(branch, branch->node)) {
        branch->node++; // consume top-level node
    }
    return false;
}

/// Matches the given input stream against the global regex,
/// returning true if input matches the regex.
bool reMatch(FILE* input) {
    inputfile = input;
    addBranch(0, &root.elems[0]);
    advanceInput(&branches[0]);

    while (branchcount > 0) {
        for (int idx = 0; idx < branchcount; idx++) {
            if (branchHasMatch(&branches[idx])) {
                return true;
            }
        }
    }
    return false;
}
