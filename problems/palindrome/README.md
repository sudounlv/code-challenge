Palindrome Recognizer
=====================
For this problem, you will need to analyze some strings and determine whether
or not they are palindromes. A palindrome is a sequence of letters for which
reversing the sequence causes no change. For a canonical example, the word
"racecar" spelled backward is also "racecar".

Your program will operate on phrases, for which the condition for being a
palindrome is relaxed in the following ways:
- Upper case and lower case letters are the same
    - "RaceCar" is a palindrome)
- All non-alphabetical characters are ignored
    - "Race! Car!!" is a palindrome

Input
-----
A phrase will be provided on each line of the input.

### Sample Input
    No lemons, no melon.
    I'm, alas, a salami.
    "Desserts!", I stressed.
    On decaf, face down.
    Step on no pets.
    An Iranian Narnia.
    Lager, sir, is regal.
    Palindrome.
    Damn. I, Agassi, miss again. Mad.

Output
------
For each line of input, one line of output should be produced: "Yes" if the
phrase is a palindrome, otherwise "No".

### Sample Output
    Yes
    Yes
    Yes
    No
    Yes
    No
    Yes
    No
    Yes
