#include <bits/stdc++.h>
using namespace std;

const int MX = 100;

int a, R, C, Q, r1, c1, r2, c2, psa[MX][MX];

int main(){
    ios_base::sync_with_stdio(0); cin.tie(NULL);  cout.tie(NULL); 
    cin >> R >> C;
    for(int r=1; r<=R; r++){
        for(int c=1; c<=C; c++){
            cin >> a;
            psa[r][c] = psa[r-1][c] + psa[r][c-1] - psa[r-1][c-1] + a;
        }
    }
    cin >> Q;
    while(Q--){
        cin >> r1 >> c1 >> r2 >> c2;
        cout << psa[r2][c2] - psa[r1-1][c2] - psa[r2][c1-1] + psa[r1-1][c1-1] << '\n';
    }
    return 0;
}

/*
4 4
1 2 3 4 
6 7 8 9
1 2 3 4
6 7 8 9
3
2 2 4 4
2 3 4 4
3 1 4 2
*/