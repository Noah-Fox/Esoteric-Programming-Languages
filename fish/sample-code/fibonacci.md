# Fibonacci Sequence Implementations

## fibonacci.txt

This commands inputs a value _n_, then outputs the first _n_ values of the fibonacci sequence. It has the following code structure:

`i01`   -   Push the input, 0, and 1 to the stack (_n_, _a_, and _b_)

`r:?!;1-r`  -   If _n_ = 0, return. Else, decrement _n_

`:@@:`  - Rearrange stack to be (_n_, _b_, _b_, _a_, _a_)

`n` -   Output _a_

`+` - Add _a_ and _b_, setting stack to (_n_, _b_, _a+b_)

`ao`    -   Output a newline


## fibonacci-golf.txt

This program is designed for a code golf problem. It outputs the first 31 values of the fibonacci sequence.

## fibonacci-recurse.txt

This program finds the _n_th value of the fibonacci sequence recursively, demonstrating fish's ability to implement functions. Due to the recursion, though, the running time is exponential.

The program either takes a preset value inside the stack as _n_, or sets it equal to 10.

The instructions for implementing a function are as follows. x1 and y1 are the position to return to after the function ends. x2 and y2 are the position that the function starts at. n1 and n2 are the inputs of the function, and f1 is the output.

1. Create a new stack containing [x1, y1, n1, n2]
2. Go to position (x2, y2)
3. Perform function using inputs. End with the stack containing [x1, y1, f1]
4. Rotate the stack twice and return to position (x1,y1)
5. Close the stack, placing f1 on the top of your original stack.

## fibonacci-memo.txt

This program finds the _n_th value of the fibonacci sequence recursively, but uses memoization to vastly improve its speed. It places the solution for _k_ at position (_k_,-1)
