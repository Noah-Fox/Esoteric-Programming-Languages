# John Conway's Game of Life

Game of Life is a cellular automaton created by mathematician John Conway. It consists of an "infinite" grid of cells, which can one of two states, live or dead. Each cell is affected by its eight adjacent neighbors. The cells change simultaneously in distinct steps, according to the following rules:
1. Any live cell with less than two neighbors dies from underpopulation.
2. Any live cell with two or three live neighbors lives.
3. Any live cell with more than three live neighbors dies from overpopulation. 
4. Any dead cell with exactly three live neighbors becomes a live cell.

Despite its simplicity, Game of Life is Turing Complete. This is due to its ability to simulate Turing machines. 

## Using the Simulator

The given interpreter/simulator will input a grid from a text file, run a given number of generation steps on it, and output the result to the same file. It takes 'O' as dead cells, and 'X' as live cells. 

The possible arguments that you can give when calling the program are:
 - inputFile: the name of the file to read from and write to
- gridWidth: the total width of the grid
- gridHeight: the total height of the grid 
      - gridWidth and gridHeight can be greater than the width or height of the grid given in the input file. Extra space will be filled with dead cells
- inputX: the x position of the top left cell of the input grid within the whole grid
- inputY: the y position of the top left cell of the input grid within the whole grid
- generations: the number of steps to take before outputting

Valid program calls are:

 `./life inputFile`            

 - Runs a single generation on the input grid, adding no extra size

`./life inputFile generations`

- Runs given number of generations on the input grid

 `./life inputFile gridWidth gridHeight inputX inputY generations`
