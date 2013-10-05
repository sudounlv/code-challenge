Branch History
==============
In this challenge, you will implement a feature similar to `git log` on a
mock version control repository.

Input
-----

### stdin
The number of commits will be provided on a line, followed by all the commits,
followed by the number of refs on its own line, followed by all the refs.

#### Commits

Commits consist of two lines of input followed by a blank line. The first
line contains the indices of the parent commit(s). The second line contains
the commit message.

The commits form a DAG (directed acyclic graph). Each commit may have 0,
1, or 2 parent commits, which are given as two integer indices. `-1` means
that the index is null and should be ignored.

Commits are given in chronological order.

#### Refs

Each ref will be specified by one line of input. This will be a name
(no spaces), followed by a space, followed by a number which is the index
of the commit that it points to.

### args

One argument will be provided to the program on the command line. This will
be the name of the ref for which to print the log.

### Sample input
    11
    -1 -1
    Initial commit.

    0 -1
    1. Added some files.

    1 -1
    2. Fixed a bug.

    2 -1
    3. Modified the word generator; now more cromulent

    3 -1
    4. Fixed 23 bugs in new generator

    2 -1
    5. Bug fix in load balancer

    4 5
    6. Merge bug fixes into wordgen branch

    5 -1
    7. Optimize bean counter for performance

    7 -1
    8. Parallelize bean counter

    5 8
    9. Merge parallel bean counter into master

    9 -1
    10. Update README

    3
    master 10
    wordgen 6
    fastbeans 8

Note: Numbers at the start of commit messages are provided as a convenience for debugging.
They do not need to be parsed; commits will always be provided in chronological order, starting
at index 0.

Output
------
Starting from the commit pointed to by the specified ref, the program should
walk the DAG and print out the commit messages for each ancestor commit in
*reverse* chronological order.

### Sample output

`./branch_history wordgen < sample-input.txt`

    6. Merge bug fixes into wordgen branch
    5. Bug fix in load balancer
    4. Fixed 23 bugs in new generator
    3. Modified the word generator; now more cromulent
    2. Fixed a bug.
    1. Added some files.


Hints / Suggestions
-------------------
- Breadth-first traversal
    - Maintain a set sorted by index for open nodes
- Depth-first traversal
    - Use std::set to de-duplicate nodes
    - Output after traversal

