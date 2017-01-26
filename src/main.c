#include <stdio.h>
#include <string.h>
#include "parse.h"
#include "ast.h"
#include "match.h"

int main(int argc, char** argv) {
    if (argc != 2 && argc != 3) {
        printf("usage: %s regex-pattern [--print-ast]\n", argv[0]);
        return 1;
    }

    reParse(argv[1]);

    if (argc == 3 && strcmp(argv[2], "--print-ast") == 0) {
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
