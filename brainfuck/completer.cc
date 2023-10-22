/**
 * Takes a function from createdCode.txt and modifies it to work with given cell variables
 * prints the modified function to the terminal
 * Implement by calling:    ./bf-copy "functionName(A1;B2;C3)"
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

struct Var{
    Var(){name = '?';pos = -1;}
    Var(char n, int p){name = n;pos = p;}
    char name;
    int pos;
};

void changeCellName(const vector<char>& pNames, const vector<Var>& vNames, char& useName){
    char changeName = useName;
    for (int i = 0; i < pNames.size(); i ++){
        if (useName == pNames[i]){
            changeName = vNames[i].name;
        }
    }
    useName = changeName;
}

int main(int argc, char const *argv[]){

    ifstream codeFile;
    codeFile.open("createdCode.txt");

    string functions;
    char gotChar;

    //copying file to a string
    if (!codeFile.fail()){
        while (!codeFile.eof()){
            codeFile.get(gotChar);
            functions += gotChar;
        }
    }
    codeFile.close();


    string searchFor;//name of the function
    vector<Var> variables;//variables to be used in function
    int charOn = 0;
    if (argc == 2){
        string funCall = argv[1];
        while (funCall[charOn] != '('){
            searchFor += funCall[charOn];
            charOn ++;
        }
        charOn ++;
        while (funCall[charOn] != ')'){
            Var gotVar(funCall[charOn],0);
            string gotDigits;
            charOn ++;
            while (isdigit(funCall[charOn])){
                gotDigits += funCall[charOn];
                charOn ++;
            }
            gotVar.pos = stoi(gotDigits);
            variables.push_back(gotVar);
            if (funCall[charOn] == ';'){
                charOn ++;
            }
        }
        
    }

    //string searchFor = "BitFlipper";

    //variables given for parameters of function
    /*vector<Var> variables;
    Var a('C',0);
    Var b('D',2);
    variables.push_back(a);
    variables.push_back(b);*/

    //parameters of function
    vector<char> params;
    
    //searching through functions for given name
    string funName;
    charOn = 0;
    while (funName != searchFor){
        funName = "";
        while (functions[charOn] != '$'){
            charOn ++;
        }
        charOn ++;
        if (functions[charOn] == '!'){
            break;
        }
        while (functions[charOn] != '('){
            funName += functions[charOn];
            charOn ++;
        }
    }

    //going through parameters for function
    if (funName != searchFor){
        return 0;
    }
    charOn ++;
    while (functions[charOn] != ')'){
        if (functions[charOn] != ';'){
            params.push_back(functions[charOn]);
        }
        charOn ++;
    }

    
    if (params.size() != variables.size()){
        return 0;
    }
    //going to beginning of function code
    while (functions[charOn] != '{'){
        charOn ++;
    }
    charOn ++;
    string copiedFun;
    //copying code to copiedFun
    char useChar;
    string inPar;
    while (functions[charOn] != '}'){
        useChar = functions[charOn];

        if (useChar == '('){
            inPar = "";
            bool hasMover = false;
            while (functions[charOn] != ')'){
                useChar = functions[charOn];
                if (useChar == '<' || useChar == '>'){
                    hasMover = true;
                }
                changeCellName(params,variables,useChar);
                inPar += useChar;
                charOn ++;
            }
            inPar += functions[charOn];
            if (hasMover){
                Var cell1;
                Var cell2;
                for (int i = 0; i < variables.size(); i ++){
                    if (variables[i].name == inPar[1]){
                        cell1 = Var(variables[i]);
                    }
                    if (variables[i].name == inPar[2]){
                        cell2 = Var(variables[i]);
                    }
                }
                inPar = '(';
                inPar += cell1.name;
                inPar += cell2.name;
                if (cell1.pos < cell2.pos){
                    for (int i = 0; i < cell2.pos-cell1.pos; i ++){
                        inPar += '>';
                    }
                }
                else{
                    for (int i = 0; i < cell1.pos-cell2.pos; i ++){
                        inPar += '<';
                    }
                }
                inPar += ')';
                copiedFun += inPar;
            }
            else{
                copiedFun += inPar;
            }
        }
        else{
            //switch any cell names to variable names
            /*for (int i = 0; i < params.size(); i ++){
                if (functions[charOn] == params[i]){
                    useChar = variables[i].name;
                }
            }*/
            changeCellName(params,variables,useChar);

            copiedFun += useChar;
        }

        charOn ++;
    }

    cout << copiedFun << endl;
    
    
    return 0;
}
