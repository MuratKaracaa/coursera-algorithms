//
//  scc.h
//  stanford
//
//  Created by Murat Karaca on 11/15/24.
//

#include <vector>
#include <map>

struct Vertex {
    int label;
    bool visited;
    std::vector<int> adjacentVertexes;
};

std::map<int, std::vector<int>> scc(std::vector<Vertex>& actualGraph, std::vector<Vertex>& reversedGraph);
