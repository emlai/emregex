# Weekly reports

## Week 3

Time used: ~2 hours

- Implemented character classes for matching digits (`\d`) and
  non-digits (`\D`).
- Implemented contiguos range expressions (e.g. `[a-z]`), and
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
