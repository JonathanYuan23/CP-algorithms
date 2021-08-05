#include<bits/stdc++.h>
using namespace std;

int main(){
    srand(time(0));
    // length of sequence
    int n;  cin >> n;
    for(int tc=0; tc<10; tc++){
        int *a = new int[n];

        // integer between 0 and 1
        // for(int i=0; i<n; i++) a[i] = rand() % 2;

        // integer between 1 and 10
        for(int i=0; i<n; i++) a[i] = rand() % 10 + 1;

        for(int i=0; i<n; i++) cout << a[i] << ' ';
        cout << '\n';
        delete a;
    }
    return 0;
}

// https://www.programiz.com/cpp-programming/library-function/cstdlib/srand
// how rand() function works is that it generates a random number from the seed provided to the srand() function, you then mod by the upper bound and add the lower bound of the range you want to generate. Why does this work? Let's say you want to generate a number between 1-10, any number mod 10 is at most 9, then adding 1, at most 10