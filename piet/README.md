# Piet

Piet scripts take the form of images constructed from twenty given colors. The image is divided into codels (which are usually single pixels). Blocks of touching codels of the same color form commands. A Piet program is iterated through by a Direction Pointer (DP), which starts at the top left block pointing right. After a command is run, the DP will move in its stored direction to a block adjacent to the furthest codel of the current block in that direction. The DP also has a Codel Chooser (CC), which has possible states Left and Right. If there are multiple valid blocks that the DP could go to, it goes to the one in the furthest direction of the CC. If there are no valid blocks, it switches the CC. If there are still none, it rotates direction clockwise, and repeats. If it returns to its initial state without moving on to another block, the program halts. This is the only way a program can end.

Piet is a stack-based language, meaning that all data memory is stored in a stack (although, as you will see, the Duplicate and Roll commands use memory outside of the stack, allowing this to be Turing-complete).


| Light red (#FFC0C0) | Light yellow (#FFFFC0) | Light green (#C0FFC0) | Light cyan (#C0FFFF) | Light blue (#C0C0FF) | Light magenta (#FFC0FF) |
| Red (#FF0000) | Yellow (#FFFF00)| Green (#00FF00) | Cyan (#00FFFF) | Blue (#0000FF) | Magenta (#FF00FF) |
| Dark red (#C00000) | Dark yellow (#C0C000) | Dark green (#00C000) | Dark cyan (#00C0C0) | Dark blue (#0000C0) | Dark magenta (#C000C0) |

Out of the twenty colors, two are non-operational. White codels allow the DP to pass through with no effect. Black codels completely block the DP. The remaining colors are organized by hue and lightness. There are six hues: red, yellow, green, cyan, blue, and magenta. Each hue has three lightnesses: light, normal, and dark. The command run by the DP is determined the hue and lightness of the current block relative to the previous block. For example, the command run when going from Light Red to Yellow is the same as going from Blue to Dark Magenta (+1 hue, +1 lightness). The possible commands are:
- `Push`:  *No change in hue, 1 step darker* - Pushes the number of codels in the previous block onto the stack
- `Pop`: *No change in hue, 2 steps darker* - Removes the top value of the stack
- `Add`: *1 step in hue, no change in lightness* - pops the top two values of the stack and pushes their sum 
- `Subtract`: *1 step in hue, 1 step darker* - pops the top two values of the stack and pushes the second-top value minus the top value
- `Multiply`: *1 step in hue, 2 steps darker* - pops the top two values of the stack and pushes their product
- `Divide`: *2 steps in hue, no change in lightness* - pops the top two values of the stack and pushes the second-top value divided by the top value
- `Modulo`: *2 steps in hue, 1 step darker* - pops the top two values of the stack and pushes the second-top value modulo the top value
- `Not`: *2 steps in hue, 2 steps darker* - pops the top value of the stack and pushes its negation (1 if it is 0, 0 if else)
- `Greater`: *3 steps in hue, no change in lightness* - pops the top two values of the stack. If the second-top value is greater than the top, pushes 1. Else, pushes 0
- `Pointer`: *3 steps in hue, 1 step darker* - pops the top value of the stack, and rotates the DP clockwise that many times
- `Switch`: *3 steps in hue, 2 steps darker* - pops the top value of the stack, and switches the state of the CC that many times
- `Duplicate`: *4 steps in hue, no change in lightness* - pushes a copy of the top value onto the stack
- `Roll`: *4 steps in hue, 1 step darker* - pops the top value X and second-top value Y, then rotates the top Y values on the stack upward by X
- `Input Num`: *4 steps in hue, 2 steps darker* - takes an input as a number and pushes it onto the stack
- `Input Char`: *5 steps in hue, no change in lightness* - takes an input as a character and pushes it onto the stack
- `Output Num`: *5 steps in hue, 1 step darker* - pops the top value of the stack and outputs its value as a number
- `Output Char`: *5 steps in hue, 2 steps darker* - pops the top value of the stack and outputs its value as a character

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
