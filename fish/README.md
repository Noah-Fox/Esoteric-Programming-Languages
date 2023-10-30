# ><> (Fish)

"><>" (pronounced Fish) is a two dimensional, stack-based programming language. There are three notable elements in the program:
1. The instruction field: this is the code itself. Every instruction is a single characters, placed on a coordinate grid, with the first character in the top left having the position (0,0)
2. The Instruction Pointer (IP): the IP stores a location in the instruction field and a cardinal direction. At each step of the program, it runs the instruction at its current position then moves one step in its direction. The code can alter its position and direction. 
3. Data memory: The program starts with an empty stack and a register. There are several operators that can modify the stack and register. More stacks can be added on top of the first stack, each with its own register. 


## Resources
[><> Wiki](https://esolangs.org/wiki/Fish)

[Online interpreter](https://suppen.no/fishlanguage/)

