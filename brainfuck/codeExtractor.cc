/**
 * Inputs a text file with brainfuck code, and outputs only brainfuck commands to a given file 
 * Call "./bf-extract fromFile.txt toFile.txt [num]"
 *      if only fromFile is given, it output the number of commands in the program
 *      num is optional, determines the amount of commands in one line 
 */

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char const *argv[]){

    string fromName;
    string toName;
    if (argc < 2){
        cout << "Enter exe command with code file and output file" << endl;
        return 0;
    }

    if (argc == 2){
        fromName = argv[1];
        int comAmount = 0;
        ifstream inFile;
        inFile.open(fromName);
        char com;
        inFile.get(com);
        while (!inFile.eof()){
            if (com == '<' || com == '>' || com == ',' || com == '.' || com == '-' || com == '+' || com == '[' || com == ']'){
                comAmount ++;
            }
            inFile.get(com);
        }
        inFile.close();
        cout << "Length: " << comAmount << " commands\n";
        return 0;
    }

    fromName = argv[1];
    toName = argv[2];


    string commands;
    int lineWidth = 30;
    if (argc >= 4){
        string lw = argv[3];
        lineWidth = stoi(lw);
    }

    ifstream fromFile;
    fromFile.open(fromName);
    char gotCom;
    fromFile.get(gotCom);
    int commandCount = 0;
    while (!fromFile.eof()){
        if (gotCom == '[' || gotCom == ']' || gotCom == '<' || gotCom == '>' || gotCom == ',' || gotCom == '.' || gotCom == '-' || gotCom == '+'){
            commands += gotCom;
            commandCount ++;
            if (commandCount % lineWidth == 0){
                commands += '\n';
            }
        }
        fromFile.get(gotCom);
    }
    fromFile.close();

    ofstream toFile;
    toFile.open(toName);
    toFile << commands;
    toFile.close();

    return 0;
}
