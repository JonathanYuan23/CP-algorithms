#include <bits/stdc++.h>
using namespace std;

vector<int> graph[10000], leaves, newLeaves, degree(10000, 0);

void addEdge(int to, int from){
    graph[to].push_back(from);
    graph[from].push_back(to);
}

void findCenter(int n){
    for(int i=0; i<n; i++){
        degree[i]=graph[i].size();
        if(degree[i]<=1){
            leaves.push_back(i);
            degree[i]=0;
        }
    }
    int processedLeaves=leaves.size();
    while(processedLeaves<n){
        newLeaves.clear();
        for(auto node: leaves){
            for(auto neighbour: graph[node]){
                if(--degree[neighbour]==1){
                    newLeaves.push_back(neighbour);
                }
            }
            degree[node]=0;
        }
        processedLeaves+=newLeaves.size();
        leaves=newLeaves;
    }
}

void graphReset(int n){
    leaves.clear(); 
    newLeaves.clear();
    degree.clear();
    for(int i=0; i<n; i++) graph[i].clear();
}

int main() {

    addEdge(0, 1);
    addEdge(2, 1);
    addEdge(2, 3);
    addEdge(3, 4);
    addEdge(5, 3);
    addEdge(2, 6);
    addEdge(6, 7);
    addEdge(6, 8);
    findCenter(9);
    for (auto x: leaves) cout << x << " "; cout << "\n\n";
    graphReset(9);

    addEdge(0, 1);
    addEdge(1, 2);
    addEdge(2, 3);
    addEdge(3, 4);
    addEdge(4, 5);
    addEdge(4, 6);
    findCenter(7);
    for(auto x: leaves) cout << x << " "; cout << "\n\n";
    graphReset(7);

    return 0;
}