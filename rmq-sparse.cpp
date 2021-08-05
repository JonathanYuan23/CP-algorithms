#include <bits/stdc++.h>
using namespace std;
const int MAXN=32, MAXM=1005;

long long n = 7, arr[] = {1, 2, -3, 2, 4, -1, 5}, dp[MAXN+1][MAXM], idx[MAXN+1][MAXM], logt[MAXM], mn, mnIndx;

void construct(){
    int P=floor(log2(n));
    for(int i=0; i<n; i++){
        dp[0][i] = arr[i];
        idx[0][i] = i;
    }
    for(int i=2; i<=n; i++){
        logt[i] = logt[i/2]+1;
        // this array holds log2 values for 1 to N
    }
    long long leftInterval, rightInterval;
    for(int i=1; i<=P; i++){
        for(int j=0; j+(1<<i)<=n; j++){
            leftInterval=dp[i-1][j];
            rightInterval=dp[i-1][j+(1<<(i-1))];
            dp[i][j]=min(leftInterval, rightInterval);
            // idx array holds indexes of min values
            idx[i][j]=(leftInterval<=rightInterval) ? idx[i-1][j] : idx[i-1][j+(1<<(i-1))];
        }
    }
}

void rmq(int l, int r){
    int len = r-l+1, P=logt[len];
    long long leftInterval = dp[P][l], rightInterval = dp[P][r-(1<<P)+1];
    mn=(leftInterval<=rightInterval) ? dp[P][l] : dp[P][r-(1<<P)+1];
    mnIndx=(leftInterval<=rightInterval) ? idx[P][l] : idx[P][r-(1<<P)+1];
}

int main() {

    construct();
    rmq(3, 6);
    cout << mn << " " << mnIndx << "\n";

    return 0;
}