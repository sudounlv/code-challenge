HTML Color Codes
================

Input
-----
The input will be provided on `stdin`. A color will be specified on each line, which the program must convert to its corresponding HTML color code. For each line of input the format will be one of the following:

* Three numbers separated by spaces, 0-255
* The name of one of 16 HTML colors. May be capitalized or lowercase.

### Sample input:
    80 100 10
    0 0 0
    Green
    255 255 255
    Silver
    maroon
    255 0 0

Output
------
For each line of input, the program should produce one line of output containing the HTML hex code corresponding to the specified color. This code always begins with a `#` character, followed by three upper-case, two-digit hexadecimal numbers.

### Sample output:
    #50640A
    #000000
    #008000
    #FFFFFF
    #C0C0C0
    #800000
    #FF0000
