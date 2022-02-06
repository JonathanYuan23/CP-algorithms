// https://codeforces.com/blog/entry/17973
#include<bits/stdc++.h>
using namespace std;

int n;

int main() {
    cin >> n;
    for(int i=0; i<1<<n; i++) {
        for(int j=0; j<n; j++) {
            if((1<<j) & i){
                cout << j + 1 << ' ';
            }
        }
        cout << '\n';
    }
}   