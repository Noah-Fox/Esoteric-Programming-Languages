# FRACTRAN

Created by John Conway, FRACTRAN is an esolang consisting of an integer `n` and a list of fractions. The program is run by updating `n` according to the following rules:
1. For the first fraction `f` in the list for which `n*f` is an integer, replace `n` with `n*f`
2. Repeat until there is no fraction `f` that satisfies rule 1

While remarkably simple, this language is in fact Turing Complete. Generally, "inputs" are given by constructing the `n` value with exponent values. For example, the multiplication program computes a+b by taking `n = 2^a * 3^b`, and outputs `5^(a*b)`.

## Using the FRACTRAN interpreter

Once you have used the Makefile to compile the fractran interpreter to `./fractran`, you can write a fractran program inside a text file. There are two ways you can write the programs:
1. Raw-interpreted code: this can consist of only the `n` and `f` values, in the form "`n a/b c/d e/f`". No other text is allowed

2. Interpreted code: this allows for the use of comments and input specification
- A comment is started with the `#` character. Everything in a line after `#` will be ignored.
- To give a set `n` value, you can include a number. To allow for user input, use the following format:

        { a^_ b^x c^_ d^y }
    where a, b, c, and d are the bases of the prime factorization of `n`, x and y are set exponents, and `_` characters specify user input as exponents for the given bases. For example, if the program gives `{ 2^_ 3^_ 5^1 }` and the user enters 3 and 2 as input, `n` will be initialized as 360.


The interpreter can then be run in the terminal with the following format:

    ./fractran [-r/-c] <filename> [-d]

- the `-r` flag specifies that the program will be interpreted as raw code
- the `-c` flag specifies that the program can have higher-interpreted elements, such as comments and input specification 
- the `-d` flag is optional, and allows for debugging. It will prompt for user input in the terminal, and output the result of every step of the program, pausing for user input. You can type "c" to stop the program from pausing, but still output all steps, and "f" to stop pauses and outputs. 

## Understanding FRACTRAN

While its simplicity makes it appear enigmatic at first, FRACTRAN is actually a very easily understandable language. To unpack it, look at a simple script:

    8 3/2 5/3

This program will run with the following steps:
1. 8 * 3/2 = 12 
2. 12 * 3/2 = 18 
3. 18 * 3/2 = 27 
4. 27 * 5/3 = 45    (n is no longer divisible by 2, so the second fraction is used)
5. 45 * 5/3 = 75
6. 75 * 5/3 = 125   (after this, n is not divisible by 2 or 3, so the program will halt)
7. n = 125

The sequence of `n` values my seem random, but will make much more sense if you look at their prime factorizations:
1. (2^3) * 3/2 = 12
2. (2^2 * 3^1) * 3/2 = 18
3. (2^1 * 3^2) * 3/2 = 27
4. (3^3) * 5/3 = 45
5. (3^2 * 5^1) = 75
6. (3^1 * 5^2) = 125
7. n = (5^3)

You can now see that as the program runs, the exponent of 2 in the prime factorization moves to 3, and then from 3 to 5. This makes the secret to writing in FRACTRAN clear: we are simply manipulating the exponents of the prime factorization of `n`. Looking at it this way, `n` represents an array of variables, each given by a prime base, and whose value is the prime's power. In the given program, there are three "variables" used, which we'll call v2, v3, and v5 (representing 2, 3, and 5). The program can then be rewritten as this:

```
    v2 = 3, v3 = 0, v5 = 0
    while (true){
        if (v2 >= 1){
            v2 --, v3 ++
        }
        else if (v3 >= 1){
            v3 --, v5 ++
        }
        else {
            return 
        }
    }
```

All FRACTRAN programs are just this chain of if statements, using the prime factorization of `n` as variables

## States

One important topic you need to understand in order to write in FRACTRAN is states. First, take a program that adds two numbers together
```
    {2^_ 3^_} 3/2
```
This program initializes `n` as 2^a * 3^b, and outputs 3^(a + b). You can easily see how this is done, looking at it as a set of variables v2 and v3. In every step, v2 is decreased and v3 is increased, until v2 is zero. This is arguably the simplest possible useful FRACTRAN code. As in normal computation, multiplication is only a looping of this process. However, a loop cannot be explicitly performed, the same cases must be considered in every step of the program. You therefore have to introduce states, so that the progress of the program can be preserved.

| Current State | Condition | Action | Next State |
| ----------- | ----------- | ----------- | ----------- |
| A | v7 > 0 | v7--, v3++ | A |
| A | v7 = 0 && v2 > 0 | v2 -- | B |
| A | v7 = 0 && v2 = 0 && v3 > 0 | v3 -- | A |
| A | v7 = 0 && v2 = 0 && v3 = 0 | | HALT |
| B | v3 > 0 | v3--, v5++, v7++ | B |
| B | v3 = 0 | | A |

