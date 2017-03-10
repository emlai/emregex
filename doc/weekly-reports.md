# Weekly reports

## Week 7

Time used: ~2 hours

- Generated online documentation from the doc comments using Doxygen.
  The generated docs are available [here][3].
- Finished the implementation document and the testing document.
- Wrote more usage instructions in the README.
- Fixed the command-line `--print-ast` flag to work regardless of its
  position relative to the regex pattern argument.

## Week 6

Time used: ~4 hours

- Set up Travis continuous integration.
- Found a way to generate test coverage reports. Set up Travis to do
  that after each successful build, and submit those reports to
  [Coveralls][2]. The coverage is currently at ~90%.
- Wrote some more testing documentation.

## Week 5

Time used: ~6 hours

- Implemented a dynamic resizable array type to refactor out duplicate
  `realloc` calls in multiple places that basically did the same thing.
- Made the program work with infinitely complex inputs (by amount of
  simultaneous state machine branches).
- Documented a performance benchmark on a big test input.
- Added some usage guidance to the README, as per code review feedback.
- Found a few corner-case bugs that had gone unnoticed by the test suite.
- Wrote the first version of the implementation document, with an overview
  of the program's structure and descriptions of the aforementioned bugs.

## Week 4

Time used: ~3 hours

- Implemented negated range expression, e.g. `[^abc]` and `[^a-c]`.
- Documented and wrote tests for the new stuff.
- Attempted to implement or-expression but got stuck, will continue on
  it next week. It's almost done.
- Next up: finish or-expression, refactor code to structure it better,
  implement anchors (e.g. `^` and `$`), validate user input instead of
  crashing on invalid input.

## Week 3

Time used: ~2 hours

- Implemented character classes for matching digits (`\d`) and
  non-digits (`\D`).
- Implemented contiguous range expressions (e.g. `[a-z]`), and
  non-contiguous range expressions (e.g. `[aeiou]`).
- Doc-commented all the new functionality.
- Wrote tests for the new functionality.
- Next up: more features, for example range negation (e.g. `[^abc]`),
  and or-expression (e.g. `foo|bar`).

## Week 2

Time used: ~15 hours

- Implemented the following regex operations / special characters:
  `?`, `()`, `.`. Some restructuring was needed to make `()` work.
- Allow `.` to be escaped with backslash: `\.`.
- Wrote tests for the new features. Also added some benchmark tests.
- Wrote lots of documentation comments.
- Next up: add more features, e.g. ranges, character classes, anchors.

## Week 1

Time used: ~15 hours

- Decided on a topic: regular expression engine.
- Wrote a proof-of-concept skeleton of the program to get an idea of
  whether the topic is suitable in terms of difficulty and scope.
  Conclusion: it seems to be fine. The program currently performs the
  [star][1] operation correctly.
- Set up Git repository, and committed the source code I had so far.
  Pushed everything to GitHub.
- Wrote the project specification document.
- I learned a lot about how to implement regular expression parsing and
  string matching for the basic regex operations.
- Not exactly sure how I'm going to implement the NFA/DFA yet. We'll
  see. The material I'm using has plenty of information on this subject
  though, so this shouldn't be a problem.
- Next up: write more regex operations and possibly implement the
  NFA/DFA.

[1]: https://en.wikipedia.org/wiki/Kleene_star
[2]: https://coveralls.io/github/emlai/emregex
[3]: https://emlai.github.io/emregex/files.html
