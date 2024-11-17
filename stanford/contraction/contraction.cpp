//
//  contraction.cpp
//  stanford
//
//  Created by Murat Karaca on 11/13/24.
//

#include "contraction.h"
#include <vector>
#include <cstdlib>
#include <ctime>

Edge select(std::vector<Edge>& adjacencyList) {
    if (adjacencyList.empty()) {
        throw std::out_of_range("Cannot select from an empty vector");
    }

    int index = std::rand() % adjacencyList.size();

    return adjacencyList[index];
}

// TODO: utilize disjoint sets instead
void makeUnion(std::vector<Edge>& adjacencyList, int replacer, int replaced){
    for(Edge& edge: adjacencyList){
        if(edge.u == replaced){
            edge.u = replacer;
        }
        if(edge.w == replaced){
            edge.w = replacer;
        }
    }
    
    adjacencyList.erase(
        std::remove_if(adjacencyList.begin(), adjacencyList.end(), [](const Edge& edge) {
            return edge.u == edge.w;
        }),
        adjacencyList.end()
    );
}


int contraction(std::vector<Edge>& adjacencyList, int vertexCount){
    
    while(vertexCount > 2){
        if(adjacencyList.empty()){
            return 0;
        }
        Edge selected = select(adjacencyList);
        makeUnion(adjacencyList, selected.w, selected.u);
        vertexCount--;
    }
    
    return adjacencyList.size();
}
