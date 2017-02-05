## Building from source

1. The following dependencies are needed: a C compiler and CMake.
   To run the tests you also need Ruby.
2. Run `cmake -G "Unix Makefiles" .` to generate a build system.
3. Run `make` to build everything. This will generate an `emregex`
   executable in the project root directory.
4. Run `make test` to run the tests.
