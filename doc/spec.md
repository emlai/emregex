# emregex Specification Document

The goal of this project is to create a [regular expression][1] engine
from scratch in the C programming language with no external dependencies.
The project should produce a reusable library component, and also a
command line front-end that reads strings from standard input and checks
whether they match a given regex. The regex is passed as a command-line
argument, à la [grep][2].

The engine should be quite fast, which is why the language C was chosen.
As a reference, I will be using [material][3] kindly provided by Russ Cox,
the original author of the fast [RE2][4] regular expression engine. The
material also contains references to work done by other regular expression
gurus, most notably [Ken Thompson][5]'s finite automaton -based engines.

The end product will make use of probably at least the following data
structures: dynamic arrays, an internal representation of the regex
patterns (e.g. an [abstract syntax tree][6]), and storage for the
[NFA][7]/[DFA][8] implementation. I might use [Thompson's
construction][9] to create the NFA, and optionally convert that
further into a DFA using the [powerset construction][10] method.
The target time complexity for checking a string for a match (after
constructing the NFA/DFA) is O(n) where _n_ is the length of the string.
This means that we cannot use backtracking, and must instead simulate
all possible branches of the automaton simultaneously.

[1]: https://en.wikipedia.org/wiki/Regular_expression
[2]: https://en.wikipedia.org/wiki/Grep
[3]: https://swtch.com/~rsc/regexp/
[4]: https://github.com/google/re2
[5]: https://en.wikipedia.org/wiki/Ken_Thompson
[6]: https://en.wikipedia.org/wiki/Abstract_syntax_tree
[7]: https://en.wikipedia.org/wiki/Nondeterministic_finite_automaton
[8]: https://en.wikipedia.org/wiki/Deterministic_finite_automaton
[9]: https://en.wikipedia.org/wiki/Thompson%27s_construction
[10]: https://en.wikipedia.org/wiki/Powerset_construction
