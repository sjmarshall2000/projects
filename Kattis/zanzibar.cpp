/*
Solution to Kattis Problem "Stand on Zanzibar"
https://open.kattis.com/problems/zanzibar

by Stephen Marshall 2020
*/

#include <iostream>

using namespace std;

int main(){
    int t;
    cin >> t;
    for(int i = 0; i < t;i++){
        int last, current, minImport;
        current = 0;
        last = 1;
        
        minImport = 0;
        cin >> current;
        while (current != 0){
            int unaccountedFor = (current - (last * 2)); //could be negative
            if( unaccountedFor > 0){minImport += unaccountedFor;}
            
            last = current;
            cin >> current;
        }
        cout << endl << minImport << endl;
    }
    
    
    return 0;
    
}