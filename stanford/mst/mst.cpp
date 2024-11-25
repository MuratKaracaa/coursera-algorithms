//
//  mst.cpp
//  stanford
//
//  Created by Murat Karaca on 11/24/24.
//

#include <fstream>
#include "mst.h"
#include <set>
#include <unordered_set>

struct Edge {
    int v;
    int w;
    int length;
};

struct Comp {
    bool operator()(const Edge& first, const Edge& second) const {
        return first.length < second.length;
    }
};

std::multiset<Edge, Comp>::iterator findFirstNotInSet(
    std::multiset<Edge, Comp>& sortedItems,
    std::unordered_set<int>& uSet) {
    for (auto it = sortedItems.begin(); it != sortedItems.end(); ++it) {
        if (uSet.contains(it->v) && !uSet.contains(it->w)) {
            uSet.insert(it->w);
            return it;
        } else if(!uSet.contains(it->v) && uSet.contains(it->w)) {
            uSet.insert(it->v);
            return it;
        }
    }
    return sortedItems.end();
}

int mst(std::ifstream& file){
    int number_of_nodes, number_of_edges;
    std::multiset<Edge, Comp> edges;
    std::unordered_set<int> X;
    
    
    file >> number_of_nodes >> number_of_edges;
    
    for(int i = 0;i<number_of_edges;i++){
        int v,w,length;
        file >> v >> w >> length;
        edges.insert({v,w,length});
    }
    
    auto firstIt = edges.begin();
    X.insert(firstIt->v);
    X.insert(firstIt->w);
    int sum = firstIt->length;
    
    while(X.size() != number_of_nodes){
        auto it = findFirstNotInSet(edges, X);
        sum += it->length;
    }
    
    
    return sum;
}
