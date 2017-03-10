#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "parse.h"
#include "ast.h"
#include "match.h"

void printUsage(char** argv) {
    printf("usage: %s regex-pattern [--print-ast]\n", argv[0]);
}

int main(int argc, char** argv) {
    if (argc != 2 && argc != 3) {
        printUsage(argv);
        return 1;
    }

    char* regexPattern = NULL;
    bool printAST = false;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--print-ast") == 0) {
            printAST = true;
        } else {
            regexPattern = argv[i];
        }
    }

    if (regexPattern == NULL) {
        printUsage(argv);
        return 1;
    }

    reParse(regexPattern);

    if (printAST) {
        rePrintAST();
        return 0;
    }

    if (reMatch(stdin)) {
        printf("match\n");
        return 0;
    } else {
        printf("no match\n");
        return 1;
    }
}
