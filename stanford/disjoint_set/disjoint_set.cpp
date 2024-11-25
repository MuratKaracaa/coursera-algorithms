//
//  disjoint_set.cpp
//  stanford
//
//  Created by Murat Karaca on 11/25/24.
//

#include "disjoint_set.h"

disjoint_set::disjoint_set(int n) : parent(n), rank(n, 0) {
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
    }
}

int disjoint_set::find(int x) {
    int root = x;
    
    // for finding first
    while(parent[root] != root){
        root = parent[root];
    }
    
    // for compressing after finding, reduces further lookup times
    while(parent[x] != x){
        int current_parent = parent[x];
        parent[x] = root;
        x = current_parent;
    
    }
    
    return parent[x];
}

void disjoint_set::unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX != rootY) {
        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}
