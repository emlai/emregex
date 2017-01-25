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

    // read whole stdin to buffer
    #define INPUT_CAPACITY 1024
    char input[INPUT_CAPACITY];
    int inputsize = 0;
    int ch;

    while ((ch = getchar()) != EOF) {
        input[inputsize++] = ch;

        if (inputsize >= INPUT_CAPACITY) {
            printf("error: input is too large\n");
            return 1;
        }
    }

    input[inputsize] = '\0';

    // strip trailing newlines
    while (inputsize > 0 && input[inputsize - 1] == '\n')
        input[--inputsize] = '\0';

    if (reMatch(input)) {
        printf("match\n");
        return 0;
    } else {
        printf("no match\n");
        return 1;
    }
}
