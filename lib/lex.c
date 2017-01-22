#include <assert.h>

static const char* lexinput;
static const char* lexinputcurrent;

static inline int readchar(void) {
    return *lexinputcurrent++;
}

static inline void unreadchar(void) {
    assert(lexinputcurrent > lexinput);
    lexinputcurrent--;
}

void lexinit(const char* input) {
    lexinput = lexinputcurrent = input;
}

int lex(void) {
    return readchar();
}
