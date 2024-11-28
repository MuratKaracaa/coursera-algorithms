//
//  scc.cpp
//  stanford
//
//  Created by Murat Karaca on 11/15/24.
//

#include <vector>
#include <map>
#include "scc.h"

void dfsWithFinishingLine(std::vector<Vertex>& reversedGraph, std::vector<int>& finishingOrder,Vertex& startingVertex){
    startingVertex.visited = true;
    for(int vertextIndex : startingVertex.adjacentVertexes){
        Vertex& adjacentVertex = reversedGraph[vertextIndex];
        if(!adjacentVertex.visited){
            dfsWithFinishingLine(reversedGraph, finishingOrder ,adjacentVertex);
        }
    }
    finishingOrder.push_back(startingVertex.label);
}

void dfsWithLeader(std::vector<Vertex>& actualGraph, Vertex& startingVertex ,int& leader, std::map<int, std::vector<int>>& connectedGraphs){
    startingVertex.visited = true;
    connectedGraphs[leader].push_back(startingVertex.label);
    for(int vertexIndex: startingVertex.adjacentVertexes){
        Vertex& adjacentVertex = actualGraph[vertexIndex];
        if(!adjacentVertex.visited){
            dfsWithLeader(actualGraph, adjacentVertex, leader, connectedGraphs);
        }
    }
}

// in the input file, edges are directed, reversed graph would be, while reading the file second item -> first item and actual one first item -> second item
std::map<int, std::vector<int>> scc(std::vector<Vertex>& actualGraph, std::vector<Vertex>& reversedGraph){
    std::vector<int> finishindOrder;
    std::map<int, std::vector<int>> connectedGrapgs;
    
    for(Vertex& vertex: reversedGraph){
        if(!vertex.visited){
            dfsWithFinishingLine(reversedGraph, finishindOrder, vertex);
        }
    }
    
    for(int i = finishindOrder.size() - 1; i>= 0;i--){
        Vertex& vertex = actualGraph[finishindOrder[i]];
        if(!vertex.visited){
            int leader = vertex.label;
            dfsWithLeader(actualGraph, vertex, leader,connectedGrapgs);
        }
    }
    
    return connectedGrapgs;
}
