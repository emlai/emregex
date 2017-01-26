#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "match.h"
#include "ast.h"
#include "lex.h"

typedef struct reBranch {
    char input;
    const reNode* node;
} reBranch;

extern reNode root;

#define MAX_BRANCHES 1024
static reBranch branches[MAX_BRANCHES];
static int branchcount = 0;
static FILE* inputfile;

static inline void advanceInput(reBranch* branch) {
    int input = getc(inputfile);
    branch->input = (input == EOF || input == '\n') ? '\0' : input;
}

void killBranch(reBranch* branch) {
    assert(branchcount < MAX_BRANCHES);
    // shift elements after this branch
    int count = branchcount - (branch - branches) - 1;
    memmove(branch, branch + 1, count * sizeof(reBranch));
    branchcount--;
}

void addBranch(char input, const reNode* node) {
    assert(branchcount < MAX_BRANCHES);
    branches[branchcount].input = input;
    branches[branchcount].node = node;
    branchcount++;
}

static bool inputMatches(const char input, const int ch) {
    switch ((reToken) ch) {
        case reDot: return true;
    }
    return input == ch;
}

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
