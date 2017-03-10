# emregex Testing Document

## Automated test scripts

There's a bunch of automated testing scripts written in the Ruby
programming language in the `test/` directory. These consist of the
following:

- `tester.rb`: This is the primary test script. It feeds the `emregex`
  program various inputs and validates the output. There's some extra
  code to allow writing the test cases in a nice declarative manner,
  and to print useful error messages in case of test failure.
- `errors.rb`: This file contains test cases that make sure the
  `emregex` program responds appropriately to invalid input.
- `benchmark.rb`: This script tests that the program performs
  efficiently with various large input sets.
- `ast_printer_test.rb`: This test checks that the program outputs the
  correct abstract syntax tree with the `--print-ast` flag, given a
  sample input pattern.

All of these scripts are run automatically when the `test` target of
the build system is invoked (e.g. via `make test`). Note: the tests can
also be run with the command `ctest --output-on-failure`, which is also
required if you wish to see the error messages of failed test cases.

## Performance

The program matches a 50MB text file (`test/bigtestfile`) in approximately 2.4
seconds on the test machine when compiled with the `-O3` optimization level. The
following Bash command was used to execute and time this benchmark:

```
cat test/bigtestfile | time ./emregex 'ax*'
```

The revision used for this test was [86a231e48f8a294d37d9fe79590d5efcca5b3741][1].

For comparison, running the same thing with grep (which is famous for being
very fast) takes about 1.35 seconds on my machine. The specific grep
version I used for this is the FreeBSD grep v2.5.1. I also suppressed the output
from grep with the `-q` option to make the comparison fairer:

```
cat test/bigtestfile | time grep -q 'ax*'
```

[1]: https://github.com/emlai/emregex/tree/86a231e48f8a294d37d9fe79590d5efcca5b3741
