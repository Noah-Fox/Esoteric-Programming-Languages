/**
    Options
        -r file             input raw code from file in form "n n1/d1 n2/d2 n3/d3 ..."
*/

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

int main(int argc, char const *argv[]){

    ll n;
    vector<Fraction> fractions;

    if (argc == 1){
        cout << "HELP MENU\n";
        return 0;
    }
    string argOption = argv[1];
    if (argOption == "-r"){
        if (argc != 3){
            cout << "ERROR\n";
            return 0;
        }

        ifstream inFile;
        inFile.open(argv[2]);

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
    }

    bool halt = false;
    while (!halt){
        cout << n << ": " << primeFactorization(n) << "\n";
        halt = true;
        for (auto it = fractions.begin(); it != fractions.end(); it ++){
            if (n % (it -> den) == 0){
                n = n * (it -> num) / (it -> den);
                halt = false;
                break;
            }
        }
    }

    cout << n << ": " << primeFactorization(n) << "\n";

    return 0;
}
