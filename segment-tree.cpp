#include <bits/stdc++.h>
using namespace std;

#define MAX 100005

int N, M, arr[] = {-1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, st[MAX*4], lazy[MAX*4];

void push(int i){
    st[i] = min(st[i*2], st[i*2+1]);
}

void build(int i, int l, int r){
    if(l==r){
        st[i] = arr[l];
        return;
    }
    int mid = (l + r) / 2;
    build(i*2, l, mid);
    build(i*2+1, mid+1, r);
    push(i);
}

void update(int i, int l, int r, int pos, int val){
    if(l==r){
        st[i] = val;
        return;
    }
    int mid = (l + r) / 2;
    if(pos<=mid) update(i*2, l, mid, pos, val);
    else update(i*2+1, mid+1, r, pos, val);
    push(i);
}

void updateRange(int i, int ql, int qr, int l, int r, int val){
    if(lazy[i]!=0){
        st[i] += lazy[i];
        // if the segment tree is for rsq do st[i] += (r-l+1) * lazy[i];
        if(l!=r){
            lazy[i*2] += lazy[i];
            lazy[i*2+1] += lazy[i];
        }
        lazy[i] = 0;
    }
    if(l>=ql && r<=qr){
        st[i] += val;
        // if the segment tree is for rsq do st[i] += (r-l+1) * val;
        if(l!=r){
            lazy[i*2] += val;
            lazy[i*2+1] += val;
        }
        return;
    }
    int mid = (l + r) / 2;
    if(qr<=mid) updateRange(i*2, ql, qr, l, mid, val);
    else if(ql>mid) updateRange(i*2+1, ql, qr, mid+1, r, val);
    else{
        updateRange(i*2, ql, qr, l, mid, val);
        updateRange(i*2+1, ql, qr, mid+1, r, val);
    }
    push(i);
}

// ql and qr are the current query, l and r is the range of the current node
// smallest of range
int rmq(int i, int ql, int qr, int l, int r){
    if(lazy[i]!=0){
        st[i] += lazy[i];
        // if the segment tree is for rsq do st[i] += (r-l+1) * lazy[i];
        if(l!=r){
            lazy[i*2] += lazy[i];
            lazy[i*2+1] += lazy[i];
        }
        lazy[i] = 0;
    }
    if(l>=ql && r<=qr) return st[i];
    int mid = (l + r) / 2;
    if(qr<=mid) return rmq(i*2, ql, qr, l, mid);
    if(ql>mid) return rmq(i*2+1, ql, qr, mid+1, r);
    return min(rmq(i*2, ql, qr, l, mid), rmq(i*2+1, ql, qr, mid+1, r));
}

int print(int i, int l, int r, int pos){
    if(lazy[i]!=0){
        st[i] += lazy[i];
        // if the segment tree is for rsq do st[i] += (r-l+1) * lazy[i];
        if(l!=r){
            lazy[i*2] += lazy[i];
            lazy[i*2+1] += lazy[i];
        }
        lazy[i] = 0;
    }
    if(l==r){
        cout << st[i] << ' ';
        return st[i];
    }
    int mid = (l + r) / 2;
    if(pos<=mid) return print(i*2, l, mid, pos);
    else return print(i*2+1, mid+1, r, pos);
}

int main(){
    build(1, 1, 10);
    updateRange(1, 1, 5, 1, 10, 5);
    for(int i=1; i<=10; i++) print(1, 1, 10, i);
    return 0;
}