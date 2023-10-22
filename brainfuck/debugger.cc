/**
 * Brainfuck runner
 * Run "./bf-debug" to run "code.txt" using "input.txt"
 * Run "./bf-debug codeFile inputFile" to use other files
 * 
 * Brainfuck commands:
 *    >  go to next cell
 *    <  go to previous cell
 *    +  add 1 to current cell
 *    -  subtract 1 from current cell
 *    ,  input char from file into current cell
 *    .  output current cell
 *    [  begin while loop, using current cell as condition
 *    ]  end while loop, using current cell as condition
 * 
 * 
 * Debugger commands:
 *    "a"  continue to next command
 *    "s"  stop debugging, run the program as normal
 *    "b"  stop debugging until out of current loop
 *    "n"  stop debugging until next line
 *    "val n"  print int value of cell n, current cell if n == -1
 *    "pos"  print line and char number of command (char number only counts other commands)
 *    "k n"  stop debugging until it reaches line n
 *    "range n m"  only display cells in range n to m 
 *    "range="  output current range 
 */


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "colors.h"

using namespace std;

int main(int argc, char const *argv[]){

    //open code file
    ifstream code;
    if (argc > 1){
        code.open(argv[1]);
    }
    else{
        code.open("code.txt");
    }
    if (code.fail()){
        cout << "code failed to load" << endl;
        return 0;
    }

    //input all valid commands into a string
    string gotCode;
    char com;
    int comCount = 0;
    vector<int> comPerLine;
    while (!code.eof()){
        code.get(com);
        if (com == '<' || com == '>' || com == '.' || com == ',' || com == '[' || com == ']' || com == '+' || com == '-'){
            gotCode += com;
            comCount ++;
        }
        while (code.peek() == '\n'){
            code.ignore();
            comPerLine.push_back(comCount);
            comCount = 0;
        }
    }
    if (comCount > 0){
        comPerLine.push_back(comCount);
    }

    //the index of the command that is currently being viewed
    int commandOn = 0;

    //opening the input file
    ifstream input;
    if (argc > 2){
        input.open(argv[2]);
    }
    else{
        input.open("input.txt");
    }
    if (input.fail()){
        cout << "Input file failed" << endl;
        return 0;
    }

    //creating array of cells, and pointer to current cell
    char data[10000] = {0};
    char* ptr = data;

    //char values that print whitespaces or new lines
    int dangerChars[] = {0,7,8,9,10,11,12,13,14,15,27,32,127,-1};
    int dangerCharAmount = 14;

    //records how many cells have been accessed
    int maxCell = 0;
    int cellRange[] = {0,40};

    bool askToCont = true;
    int stoppedInLoop = 0;//use in 'b'
    int stoppedOnLine = -1;//use in 'n'
    string holdOutput = "";
    int inLoops = 0;//number of loops the program is inside
    int stopUntilLine = -1;//use in 'k'

    //Running code
    while (commandOn < gotCode.length()){
        com = gotCode[commandOn];
        if (com == '<'){
            --ptr;
        }
        else if (com == '>'){
            if (ptr == data + maxCell){
                maxCell ++;
            }
            ++ptr;
        }
        else if (com == '-'){
            --*ptr;
        }
        else if (com == '+'){
            ++*ptr;
        }
        else if (com == '.'){
            if (askToCont){
                holdOutput = *ptr;
            }
            else{
                cout << *ptr;
            }
        }
        else if (com == ','){
            while (input.peek() == '\n'){
                input.ignore();
            }
            if (input.eof()){
                *ptr = 0;
            }
            else{
                input.get(*ptr);
            }
        }
        else if (com == ']'){
            if (*ptr != 0){
                int brackets = 1;
                while (brackets > 0){
                    commandOn --;
                    if (gotCode[commandOn] == ']'){
                        brackets ++;
                    }
                    else if (gotCode[commandOn] == '['){
                        brackets --;
                    }
                }
            }else{
                //only decrease the amount of loops if it exits the loop
                inLoops --;
            }
        }
        else if (com == '['){
            if (*ptr == 0){
                int brackets = 1;
                while (brackets > 0){
                    commandOn ++;
                    if (gotCode[commandOn] == '['){
                        brackets ++;
                    }
                    else if (gotCode[commandOn] == ']'){
                        brackets --;
                    }
                }
            }else{
                inLoops ++;
            }
        }
        


        //outputting the cells, current command, and current cell position
        if (askToCont){
            //command
            cout << endl << GREEN << "Running: " << YELLOW << com << RESET << endl;

            //displaying output
            if (holdOutput != ""){
                cout << GREEN << "Output: " << MAGENTA << holdOutput << RESET << endl;
                holdOutput = "";
            }

            //cells 
            int pointerPos = -1;
            for (int i = cellRange[0]; i <= cellRange[1]; i ++){
                if (i <= maxCell){
                    if (ptr == data+i){
                        pointerPos = i-cellRange[0];
                    }
                    cout << BOLD << BLUE << '[' << RESET;

                    bool canPrint = true;
                    for (int x = 0; x < dangerCharAmount; x ++){
                        if (data[i] == dangerChars[x]){
                            canPrint = false;
                        }
                    }

                    if (canPrint){
                        cout << MAGENTA << data[i] << RESET;
                    }
                    else{
                        cout << ' ';
                    }
                    cout << BOLD << BLUE << ']' << RESET;
                }

            }
            cout << endl;

            //output pointer position
            if (pointerPos >= 0){
                for (int i = 0; i < (pointerPos+1)*3-2; i ++){
                    cout << " ";
                }
                cout << YELLOW << '^' << RESET << endl;
            }

            //Input debugging commands from user
            string wait;
            do{
                cout << GREEN << "Continue? " << RESET;
                cin >> wait;
                if (wait == "s"){
                    //stop debugging, run as normal
                    askToCont = false;
                }
                if (wait == "b" && inLoops > 0){
                    //stop debugging until out of current loop
                    askToCont = false;
                    stoppedInLoop = inLoops;
                }
                if (wait == "n"){

                    int comSum = 0;
                    int lineOn = 0;
                    while (comSum <= commandOn){
                        comSum += comPerLine.at(lineOn);
                        lineOn ++;
                    }
                    stoppedOnLine = lineOn-1;
                    askToCont = false;
                }
                if (wait == "val"){
                    int getPos;
                    cin >> getPos;
                    int gotVal;
                    if (getPos == -1){
                        gotVal = *ptr;
                        cout << CYAN << "Cell " << (ptr-data) << ": " << MAGENTA << gotVal << RESET << endl;
                    }
                    else{
                        gotVal = data[getPos];
                        cout << CYAN << "Cell " << getPos << ": " << MAGENTA << gotVal << endl;
                    }
                }
                if (wait == "pos"){
                    int comSum = 0;
                    int lineOn = 0;
                    while (comSum <= commandOn){
                        comSum += comPerLine.at(lineOn);
                        lineOn ++;
                    }
                    cout << CYAN << "Line: " << MAGENTA << lineOn << RESET << endl;
                    cout << CYAN << "Command: " << MAGENTA << commandOn-comSum+comPerLine.at(lineOn-1) << RESET << endl;
                    
                }
                if (wait == "k"){
                    //input int 
                    cin >> stopUntilLine;
                    askToCont = false;
                }
                if (wait == "range"){
                    cin >> cellRange[0];
                    cin >> cellRange[1];
                }
                if (wait == "range="){
                    cout << CYAN << "Cell Range: " << MAGENTA << cellRange[0] << " - " << cellRange[1] << RESET << endl;
                }
            }while (wait != "a" && askToCont);
        }
        else if (inLoops < stoppedInLoop){
            stoppedInLoop = 0;
            askToCont = true;
        }
        else if (stoppedOnLine >= 0){
            int comSum = 0;
            int lineOn = 0;
            while (comSum <= commandOn+1){
                if (lineOn < comPerLine.size()){
                    comSum += comPerLine.at(lineOn);
                }else{
                    comSum = commandOn+2;
                }
                lineOn ++;
            }
            if (lineOn - 1 != stoppedOnLine){
                stoppedOnLine = -1;
                askToCont = true;
            }
        }
        else if (stopUntilLine > 0){
            //determine line on
            if (stopUntilLine <= comPerLine.size()){
                int comSum = 0;
                int lineOn = 0;
                while (comSum <= commandOn+1){
                    comSum += comPerLine.at(lineOn);
                    lineOn ++;
                }
                if (lineOn >= stopUntilLine){
                    askToCont = true;
                    stopUntilLine = -1;
                }
            }
        }


        commandOn ++;
    }


    code.close();
    input.close();
    return 0;
}
