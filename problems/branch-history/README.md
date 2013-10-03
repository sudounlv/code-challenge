Branch History
==============
In this challenge, you will implement a feature similar to `git log` on a
mock version control repository.

Input
-----

### stdin
The input file will provide a list of commits followed by a list of refs.

The commits form a DAG (directed acyclic graph). Each commit may have 0,
1, or 2 parent commits, which are given as two integer indices. `-1` means
that the index is null and should be ignored.

Commits are given in chronological order.

Each ref will be specified by a name followed by a number which is the index
of the commit that it points to.

### args

One argument will be provided to the program on the command line. This will
be the name of the ref for which to print the log.

Output
------
Starting from the commit pointed to by the specified ref, the program should
walk the DAG and print out the commit messages for each ancestor commit in
chronological order.

Hints / Suggestions
-------------------
- Breadth-first traversal
    - Priority queue sorted by index for open nodes
- Depth-first traversal
    - Less efficient
    - Use std::set to de-duplicate commits
    - Sort after traversal

