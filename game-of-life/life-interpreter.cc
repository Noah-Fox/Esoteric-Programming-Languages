/*
 * Simulator for John Conway's Game of Life
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]){

    string inputFileName;
    int gridWidth = 0;
    int gridHeight = 0;
    int inputX = 0;
    int inputY = 0;
    int generations = 1;
    bool sizeGiven = false;
    vector< vector<bool> > grid;
    
    //parse arguments
    if (argc == 2){
        inputFileName = argv[1];
    }
    else if (argc == 3){
        inputFileName = argv[1];
        generations = stoi(argv[2]);
    }
    else if (argc == 7){
        inputFileName = argv[1];
        gridWidth = stoi(argv[2]);
        gridHeight = stoi(argv[3]);
        inputX = stoi(argv[4]);
        inputY = stoi(argv[5]);
        generations = stoi(argv[6]);
        grid.resize(gridWidth,vector<bool>(gridHeight,false));
        sizeGiven = true;
    }
    else {
        cout << "HELP MENU\n";
        return 0;
    }
    
    ifstream inFile;
    inFile.open(inputFileName);

    if (inFile.fail()){
        cout << "ERROR: " << inputFileName << " failed to open\n";
        return 0;
    }

    //input initial grid
    string inputLine;
    int lineCount = 0;
    while (!inFile.eof()){
        lineCount ++;
        inputLine = "";
        inFile >> inputLine;

        if (sizeGiven){
            for (int i = 0; i < inputLine.length(); i ++){
                grid[i+inputX][lineCount+inputY-1] = (inputLine[i] == 'X');
            }
        }
        else {
            if (gridWidth == 0){
                gridWidth = inputLine.length();
                grid.resize(gridWidth);
            }
            for (int i = 0; i < inputLine.length(); i ++){
                grid[i].push_back(inputLine[i] == 'X');
            }
            gridHeight = lineCount;
        }
    }

    inFile.close();


    //process generations
    for (int i = 0; i < generations; i ++){
        vector< vector<bool> > nextGrid(gridWidth,vector<bool>(gridHeight,false));
        for (int x = 0; x < gridWidth; x ++){
            for (int y = 0; y < gridHeight; y ++){
                int adjCount = 0;
                if (x > 0 && grid[x-1][y]) adjCount ++;
                if (x > 0 && y > 0 && grid[x-1][y-1]) adjCount ++;
                if (y > 0 && grid[x][y-1]) adjCount ++;
                if (y > 0 && x < gridWidth-1 && grid[x+1][y-1]) adjCount ++;
                if (x < gridWidth-1 && grid[x+1][y]) adjCount ++;
                if (x < gridWidth-1 && y < gridHeight-1 && grid[x+1][y+1]) adjCount ++;
                if (y < gridHeight-1 && grid[x][y+1]) adjCount ++;
                if (x > 0 && y < gridHeight-1 && grid[x-1][y+1]) adjCount ++;

                if (grid[x][y] && (adjCount == 2 || adjCount == 3)){
                    nextGrid[x][y] = true;
                }
                if (!grid[x][y] && adjCount == 3){
                    nextGrid[x][y] = true;
                }
            }
        }
        grid = nextGrid;
    }

    //output to file
    ofstream outFile;
    outFile.open(inputFileName);

    for (int i = 0; i < gridHeight; i ++){
        for (int x = 0; x < gridWidth; x ++){
            if (grid[x][i]){
                outFile << "X";
            }
            else {
                outFile << "O";
            }
        }
        outFile << "\n";
    }

    outFile.close();

    return 0;
}
