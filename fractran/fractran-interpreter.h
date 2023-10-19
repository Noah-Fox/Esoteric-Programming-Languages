#ifndef FRACT_INTER
#define FRACT_INTER

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

typedef unsigned long long ll;

struct Fraction{
    ll num;
    ll den;

    Fraction(ll a, ll b){num = a; den = b;}
};

string primeFactorization(ll a){
    string result = "";
    bool appended = false;
    for (ll i = 2; i <= a; i ++){
        ll count = 0;
        while (a % i == 0){
            count ++;
            a /= i;
        }
        if (count){
            if (appended) result += ",";
            result += to_string(i);
            result += "^";
            result += to_string(count);
            appended = true;
        }
    }
    return result;
}

//input an integer from the istream, even if it is part of a string
ll extractInt(istream& in){
    ll result = 0;
    while (isdigit(in.peek())){
        result = 10*result + (in.peek()-'0');
        in.ignore();
    }
    return result;
}

void parseSpaceWithComments(istream& in){
    while (!in.eof()){
        if (isspace(in.peek())){
            in.ignore();
        }
        else if (in.peek() == '#'){
            while (in.peek() != '\n'){
                in.ignore();
            }
        }
        else {
            return;
        }
    }
}

bool interpretRaw(string fileName, ll& n, vector<Fraction>& fractions){
    ifstream inFile;
    inFile.open(fileName);
    if (inFile.fail()){
        cout << "ERROR: failed to open " << fileName << "\n";
        return 0;
    }

    inFile >> n;

    while (!inFile.eof()){
        string f;
        inFile >> f;

        ll num = 0, den = 0;
        for (ll i = 0; i < f.length() && isdigit(f[i]); i ++){
            num = 10*num + (f[i]-'0');
        }
        ll ten = 1;
        for (ll i = f.length()-1; i >= 0 && isdigit(f[i]); i ++){
            den += ten * (f[i]-'0');
            ten *= 10;
        }

        fractions.push_back(Fraction(num,den));
    }

    inFile.close();

    return true;
}

bool interpretCode(string fileName, ll& n, vector<Fraction>& fractions, bool debugOutput){
    ifstream inFile;
    inFile.open(fileName);
    if (inFile.fail()){
        cout << "ERROR: failed to open " << fileName << "\n";
        return 0;
    }

    parseSpaceWithComments(inFile);

    //interpret input value
    if (isdigit(inFile.peek())){
        //n is a given value
        inFile >> n;
    }
    //n uses inputs
    else if (inFile.peek() == '{'){
        inFile.ignore();
        n = 1;

        ll base, power;

        //go through input notation
        while (true){
            parseSpaceWithComments(inFile);

            //end input
            if (inFile.peek() == '}'){
                inFile.ignore();
                break;
            }
            else if (isdigit(inFile.peek())){
                base = extractInt(inFile);

                if (inFile.peek() == '^'){
                    inFile.ignore();
                }
                else {
                    cout << "ERROR: expected '^'\n";
                    inFile.close();
                    return 0;
                }

                if (isdigit(inFile.peek())){
                    power = extractInt(inFile);
                }
                else if (inFile.peek() == '_'){
                    if (debugOutput){
                        cout << "input: ";
                    }
                    cin >> power;
                    inFile.ignore();
                }
                else {
                    cout << "ERROR: expected number or '_'\n";
                    inFile.close();
                    return 0;
                }

                n *= pow(base,power);
            }
            else {
                cout << "ERROR: expected number or end of input\n";
                inFile.close();
                return 0;
            }
        }

    }
    
    //go through fractions
    parseSpaceWithComments(inFile);
    ll num, den;
    while (!inFile.eof()){
        if (!isdigit(inFile.peek())){
            cout << "ERROR: expected number in fraction numerator\n";
            cout << "       received '" << inFile.peek() << "'\n";
            inFile.close();
            return 0;
        }

        num = extractInt(inFile);
        if (inFile.peek() != '/'){
            cout << "ERROR: expected '/' in fraction\n";
            inFile.close();
            return 0;
        }
        inFile.ignore();
        if (!isdigit(inFile.peek())){
            cout << "ERROR: expected number in fraction denominator\n";
            inFile.close();
            return 0;
        }
        den = extractInt(inFile);

        fractions.push_back(Fraction(num,den));
        parseSpaceWithComments(inFile);
    }

    inFile.close();

    return true;
}

#endif 
