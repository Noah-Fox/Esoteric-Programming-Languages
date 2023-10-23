# Piet

## Projects

decrementer.png
- Inputs a number and outputs every number from it decreasing to zero.

fibonacci
- SETUP
- input n to stack                  |n
- add 1 to stack                    |n a
- add 1 to stack                    |n a b
- LOOP
- duplicate b                       |n a b b'
- rotate top three by two:
    - add three to stack                |n a b b' 3
    - add two to stack                  |n a b b' 3 2
    - roll                              |n b b' a
- duplicate                         |n b b' a' a
- rotate top four by one:
    - add four to the stack             |n b b' a' a 4
    - add one to the stack              |n b b' a' a 4 1
    - roll                              |n a b b' a'
- add                               |n a b (a+b)
- rotate top three by two:
    - add three to stack                |n a b (a+b) 3
    - add two to stack                  |n a b (a+b) 3 2
    - roll                              |n b (a+b) a 
- output                            |n b (a+b) 
- rotate top three by two:
    - add three to stack                |n b (a+b) 3
    - add two to stack                  |n b (a+b) 3 2
    - roll                              |b (a+b) n

- print a space:
    - add 32 to stack                   |b (a+b) n 32
    - output                            |b (a+b) n
- decrement n:
    - add one to stack                  |b (a+b) n 1
    - subtract                          |b (a+b) (n-1)

- duplicate                         |b (a+b) n n'
- not                               |b (a+b) n !n
- if (!n) halt, else loop to LOOP
    - rotate DP                     |b (a+b) n
    - rotate top three by one:
        - add three to stack            |b (a+b) n 3
        - add one to stack              |b (a+b) n 3 1
        - roll                          |n b (a+b)
