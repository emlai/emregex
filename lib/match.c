#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "ast.h"

typedef struct reBranch {
    const char* input;
    const reNode* node;
} reBranch;

extern reNode stack[];
extern int stacksize;

#define MAX_BRANCHES 1024
static reBranch branches[MAX_BRANCHES];
static int branchcount = 0;

void killBranch(reBranch* branch) {
    assert(branchcount < MAX_BRANCHES);
    // shift elements after this branch
    int count = branchcount - (branch - branches) - 1;
    memmove(branch, branch + 1, count * sizeof(reBranch));
    branchcount--;
}

void addBranch(const char* input, const reNode* node) {
    assert(branchcount < MAX_BRANCHES);
    branches[branchcount].input = input;
    branches[branchcount].node = node;
    branchcount++;
}

bool branchHasMatch(reBranch* branch) {
    if (branch->node >= stack + stacksize) { // node out of bounds
        if (*branch->input != '\0') killBranch(branch);
        return *branch->input == '\0';
    }

    switch (branch->node->type) {
        case reChar:
            if (*branch->input != branch->node->ch) {
                killBranch(branch);
            } else {
                branch->input++;
                branch->node++;
            }
            break;
        case reStar:
            addBranch(branch->input, branch->node + 1);
            assert(branch->node->operand->type == reChar);

            if (*branch->input != branch->node->operand->ch) {
                killBranch(branch);
            } else {
                branch->input++;
            }
            break;
    }

    return false; // no match found yet
}

bool reMatch(const char* input) {
    addBranch(input, &stack[0]);

    while (branchcount > 0) {
        for (int idx = 0; idx < branchcount; idx++) {
            if (branchHasMatch(&branches[idx])) {
                return true;
            }
        }
    }
    return false;
}
