/*
Solution to Kattis Problem "Tajna"
https://open.kattis.com/problems/tajna

by Stephen Marshall 2020
*/
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main(){
    int n, r, c;
    string line;
    getline(cin, line);
    n = line.length();
    cout << endl << n << endl;

    for(int i = 1; i <= n; i++){//i is r
        for(int j = i; j <= n; j++){ //j is c
        cout << i << " "<< j << " " << (i * j) << endl;
            if(j * i == n){
                r = i;
                c = j;
                cout << "set" << endl;
            }
        }
    }
    string answer;
    cout << "r:"<<r<<endl<<"c:"<<c<<endl;
    for(int i = 0; i < c; i++){//for every collumn
        for(int j = 0; j < r; j++){//for every row
            cout << "i:"<<i<<"\tj:"<<j<<"\t";
            int x = (r *j) + (i);
            cout << "index:"<<x<<endl;
            answer += line[x];

        }
    }

    cout << answer << endl;






    return 0;
}