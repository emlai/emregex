# emregex Implementation Document

This document describes the inner workings of the emregex regular expression
engine.

## Architecture

emregex follows a library-based design. The reusable components have been
extracted to their own library named `libemregex` (implemented in the `lib`
directory, with the public header files in the `include` directory),
allowing for reuse in other programs or libraries. The command-line
interface (i.e. the `emregex` program) to this library is implemented in the
`src` directory.

## Algorithm

The parsing and regex matching algorithm consists of the following steps:

1. The program first [tokenizes][1] the input regex pattern. This is implemented
   in `lib/lex.c` and `lib/lex.h`.
2. After tokenizing the input regex pattern, the program builds a tree
   representation of it. The tree structure, called the [AST][2], is implemented
   in `include/ast.h`. The algorithm that constructs the AST is called the
   [parser][3], and is implemented in `lib/parse.c`.
3. After the AST has been constructed, the program starts matching its standard
   input stream (until [EOF][4]) against the regex pattern. The matching
   algorithm is implemented in `lib/match.c`. It currently does the matching by
   traversing the AST (which is quite slow, and could be optimized to use a
   [nondeterministic finite automaton][5] instead). The matcher doesn't use
   backtracking in order to achieve better performance. Instead, it simulates
   all possible branches of the [state machine][6] simultaneously, as described
   in [Regular Expression Matching Can Be Simple And Fast][7] by Russ Cox.
   The program stops as soon as it finds out what the result is, and doesn't
   simulate any possible remaining branches after that point.

## Bugs

There are currently some known bugs with unknown causes:

- Matching the input string `ax` against the regex `ax+` gives the wrong result.
- Matching the input string `ax` against the regex `a*a` gives the wrong result.

[1]: https://en.wikipedia.org/wiki/Lexical_analysis
[2]: https://en.wikipedia.org/wiki/Abstract_syntax_tree
[3]: https://en.wikipedia.org/wiki/Parsing
[4]: https://en.wikipedia.org/wiki/End-of-file
[5]: https://en.wikipedia.org/wiki/Nondeterministic_finite_automaton
[6]: https://en.wikipedia.org/wiki/Finite-state_machine
[7]: https://swtch.com/~rsc/regexp/regexp1.html
