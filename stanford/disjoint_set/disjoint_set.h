//
//  disjoint_set.h
//  stanford
//
//  Created by Murat Karaca on 11/25/24.
//

#include <vector>
#include <unordered_set>

#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

class disjoint_set {
private:
    std::vector<int> parent;
    std::vector<int> rank;

public:
    disjoint_set(int n);
    
    int find(int x);
    void unite(int x, int y);
};

#endif

