#include <stdio.h>
#include <string.h>
#include "parse.h"
#include "ast.h"
#include "match.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("usage: %s regex-pattern\n", argv[0]);
        return 1;
    }

    parse(argv[1]);

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

    if (match(input)) {
        printf("match\n");
        return 0;
    } else {
        printf("no match\n");
        return 1;
    }
}
