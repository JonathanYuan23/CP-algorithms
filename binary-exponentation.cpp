#include <bits/stdc++.h>
#define MOD 1000000007
using namespace std;

template <typename T1, typename T2, typename T3> 
T1 binary_pow(T1 base, T2 exp, T3 mod){
    if(exp == 0) return 1;
    T1 temp = binary_pow(base, exp / 2);
    temp = temp * temp % mod;
    if(exp % 2 == 0) return temp;
    return temp * base % mod;    
}

int main() {
    cout << binary_pow(2, 4, MOD) << "\n";
}