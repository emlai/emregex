# emregex

[![Build Status](https://travis-ci.org/emlai/emregex.svg?branch=master)](https://travis-ci.org/emlai/emregex)
[![Coverage Status](https://coveralls.io/repos/github/emlai/emregex/badge.svg)](https://coveralls.io/github/emlai/emregex)

## Building from source

1. The following dependencies are needed: a C compiler and CMake.
   To run the tests you also need Ruby.
2. Run `cmake -G "Unix Makefiles" .` to generate a build system.
   If you wish to compile a release build with optimizations, add
   the flag `-DCMAKE_BUILD_TYPE=Release` to the command.
3. Run `make` to build everything. This will generate an `emregex`
   executable in the project root directory.
4. Run `ctest --output-on-failure` to run the tests, reporting any
   errors in case of test failure. `make test` can also be used to
   run the tests, but it doesn't print any error messages for
   failing test cases.

## Usage

The `emregex` executable works pretty much like `grep`, except
that it matches the whole input string, and currently only reads
from standard input. This means that the most useful way to use
it is to pipe something to it, e.g. like this:

```
echo "text to match" | ./emregex "regex pattern"
```

The program prints `match` and exits with the status 0 if the
given string matches the regex passed as the argument, or
`no match` with a non-zero exit status if it doesn't.

You can also print the abstract syntax tree of the parsed regex
pattern by invoking `emregex` with the `--print-ast` flag. This
might be useful for e.g. debugging the program.
