/**
 * Brainfuck runner
 * Run "./bf" to run "code.txt" using "input.txt"
 * Run "./bf codeFile inputFile" to use other files
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
 */


#include <iostream>
#include <fstream>
#include <string>

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
    while (!code.eof()){
        code.get(com);
        if (com == '<' || com == '>' || com == '.' || com == ',' || com == '[' || com == ']' || com == '+' || com == '-'){
            gotCode += com;
        }
        while (code.peek() == '\n'){
            code.ignore();
        }
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

    //records how many cells have been accessed
    int maxCell = 0;

    while (commandOn < gotCode.length()){
        com = gotCode[commandOn];
        if (com == '<'){
            --ptr;
        }
        else if (com == '>'){
            ++ptr;
            maxCell ++;
        }
        else if (com == '-'){
            --*ptr;
        }
        else if (com == '+'){
            ++*ptr;
        }
        else if (com == '.'){
            cout << *ptr;
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
            }
        }
        commandOn ++;
    }


    code.close();
    input.close();
    return 0;
}
