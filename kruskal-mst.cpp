#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
typedef pair<int, int> pii;
typedef pair<pair<int, int>, int> piii;

class UnionFind {                                             
private:
  vector<int> p, rank;                   
public:
  UnionFind(int N) {
    rank.assign(N, 0);
    p.assign(N, 0); 
    for (int i = 0; i < N; i++) p[i] = i; 
  }
  int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }

  bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }

  void unionSet(int i, int j) { 
    if (!isSameSet(i, j)) { 
      int x = findSet(i), y = findSet(j);
      if (rank[x] > rank[y]) p[y] = x;
      else { 
        p[x] = y;
        if (rank[x] == rank[y]) rank[y]++; 
      } 
    }                       
  }
};

bool comp(piii a, piii b){
    return a.se < b.se;
}

int n, e;  
vector<piii> edges; vector<pii> mst[10000]; vector<piii> mstEdges;

int main() {
    cin >> n >> e;
    UnionFind uSet(n);
    int u, v, c;
    for(int i=0; i<e; i++){
        cin >> u >> v >> c;
        edges.push_back({{u, v}, c});
    }
    sort(edges.begin(), edges.end(), comp);
    int cost=0;
    for(auto E: edges){
        u=E.fi.fi; v=E.fi.se, c=E.se;
        if(uSet.findSet(u)!=uSet.findSet(v)){
            cost+=c;
            uSet.unionSet(u, v);
            mstEdges.push_back({{u, v}, c});
            mst[u].push_back({v, c});
            mst[v].push_back({u, c});
        }
    }
    return 0;
}