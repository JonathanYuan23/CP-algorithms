// sqrt-decomposition for rsq using 0-based indexing
#include <bits/stdc++.h>
using namespace std;

int blocks[10000], arr[10000], pending[10000], blocks_size;

int preprocess(int n) { 
    int current_blocks = -1; 
    blocks_size = sqrt(n); 
   
    for (int i=0; i<n; i++) { 
        if (i % blocks_size == 0) { 
            current_blocks++;  //new blocks
        } 
        blocks[current_blocks] += arr[i]; 
    } 
    
    return blocks_size;
}

int query(int blocks_size, int l, int r) { 
    int sum = 0; 
    
    //loop the first blocks
    //until we reach r or a starting index
    while (l < r && l % blocks_size != 0) { 
        sum += arr[l] + pending[l/blocks_size]; 
        l++; 
    } 
    //Loop until we reach
    //blocks that contains r
    while (l + blocks_size <= r) {  
        sum += blocks[l / blocks_size]; 
        l += blocks_size; 
    } 
    
    //loop until r
    while (l<=r) { 
        sum += arr[l] + pending[l/blocks_size]; 
        l++; 
    } 

    return sum; 
}

void rangeAdd(int l, int r, int val) { 

    while (l < r && l % blocks_size != 0) { 
        blocks[l / blocks_size] += val;
        arr[l] = (arr[l] + val); 
        l++; 
    } 
    while (l + blocks_size <= r) {  
        blocks[l / blocks_size] += val * blocks_size; 
        pending[l / blocks_size] += val;
        l += blocks_size; 
    } 
    while (l<=r) { 
        blocks[l / blocks_size] += val;
        arr[l] = (arr[l] + val); 
        l++; 
    } 
}

void update(int blocks_size, int i, int val) { 
    int blocks_no = i / blocks_size; 
    blocks[blocks_no] -= arr[i];
    blocks[blocks_no] += val;
    arr[i] = val;
}

int main() {
    return 0;
}