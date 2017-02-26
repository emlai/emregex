# emregex

[![Build Status](https://travis-ci.org/emlai/emregex.svg?branch=master)](https://travis-ci.org/emlai/emregex)
[![Coverage Status](https://coveralls.io/repos/github/emlai/emregex/badge.svg)](https://coveralls.io/github/emlai/emregex)

## Building from source

1. The following dependencies are needed: a C compiler and CMake.
   To run the tests you also need Ruby.
2. Run `cmake -G "Unix Makefiles" .` to generate a build system.
3. Run `make` to build everything. This will generate an `emregex`
   executable in the project root directory.
4. Run `make test` to run the tests.

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
