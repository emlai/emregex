# emregex Testing Document

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
