/**
    Options
        -r file             Input raw code from file in form "n n1/d1 n2/d2 n3/d3 ..."
        -c file             Input code from file, allowing comments using "#" and input specification
                            using {a^_ b^x c^_ d^y} notation
        -d                  Output each step and pause for user input during program run. Enter "c" to
                            stop pauses, Enter "f" to stop pauses and stop outputs until program halts
*/

//NOTE: all numbers in code must currently fit inside an unsigned long long. Numbers generated in code can be as big as any 
// number whose prime factorization is represented by unsigned long longs.

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "fractran-interpreter.h"

using namespace std;

typedef unsigned long long ll;

int main(int argc, char const *argv[]){

    map<ll,ll> n;
    vector<Fraction> fractions;

    if (argc == 1){
        cout << "HELP MENU\n";
        return 0;
    }

    bool rawInterpret = true;
    bool debugOutput = false;
    bool pauseWithDebug = true;
    string fileName = "";

    //go through arguments
    for (ll i = 1; i < argc; i ++){
        string argOption = argv[i];
        if (argOption == "-r"){
            if (i == argc-1){
                cout << "ERROR: invalid arguments. Expected a file\n";
                return 0;
            }
            i ++;
            fileName = argv[i];
        }
        else if (argOption == "-c"){
            if (i == argc-1){
                cout << "ERROR: invalid arguments. Expected a file\n";
                return 0;
            }
            rawInterpret = false;
            i ++;
            fileName = argv[i];
        }
        else if (argOption == "-d"){
            debugOutput = true;
        }
    }

    //interpret code
    if (rawInterpret){
        bool goodCode = interpretRaw(fileName, n, fractions);
        if (!goodCode){
            return 0;
        }
    }
    else {
        bool goodCode = interpretCode(fileName, n, fractions, debugOutput);
        if (!goodCode){
            return 0;
        }
    }

    //run program
    bool halt = false;
    while (!halt){
        halt = true;
        for (vector<Fraction>::iterator it = fractions.begin(); it != fractions.end(); it ++){
            if (makesInteger(n,*it)){
                multiplyToInteger(n,*it);
                if (debugOutput){
                    cout << (it -> numVal) << "/" << (it -> denVal) << ": " << " " << primeFactorization(n) << "\t";
                    if (pauseWithDebug){
                        string debugInput;
                        cin >> debugInput;
                        if (debugInput == "c"){
                            pauseWithDebug = false;
                        }
                        else if (debugInput == "f"){
                            debugOutput = false;
                        }
                    }
                    else {
                        cout << "\n";
                    }
                }
                halt = false;
                break;
            }
        }
    }

    cout << primeFactorization(n) << "\n";

    return 0;
}
