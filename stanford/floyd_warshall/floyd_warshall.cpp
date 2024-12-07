//
//  floyd_warshall.cpp
//  stanford
//
//  Created by Murat Karaca on 12/1/24.
//

#include "floyd_warshall.h"
#include <iostream>

#define INF std::numeric_limits<int>::max()

int floyd_warshall(std::ifstream& file) {
    int number_of_vertices, number_of_edges;
    file >> number_of_vertices >> number_of_edges;
    std::vector<FloydEdge> edges;
    std::vector<std::vector<int>> dist(number_of_vertices, std::vector<int>(number_of_vertices, INF));
    
    for(int i = 0;i<number_of_edges;i++){
        int u,v,weight;
        file >> u >> v >> weight;
        edges.push_back({u-1,v-1,weight});
    }
    
    for (int i = 0; i < number_of_vertices; ++i){
        dist[i][i] = 0;
    }

    for (const auto& edge : edges) {

        if (dist[edge.u][edge.v] > edge.weight){
            dist[edge.u][edge.v] = edge.weight;
        }
    }
    
    for (int k = 0; k < number_of_vertices; ++k) {
        for (int i = 0; i < number_of_vertices; ++i) {
            if (dist[i][k] == INF)
                continue;
            for (int j = 0; j < number_of_vertices; ++j) {
                if (dist[k][j] == INF)
                    continue;
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    
    for (int i = 0; i < number_of_vertices; ++i) {
        if (dist[i][i] < 0) {
            std::cout << "Graph contains a negative weight cycle\n";
            return -1;
        }
    }
    
    int min = INF;
    
    for (int i = 0; i < number_of_vertices; ++i) {
        for (int j = 0; j < number_of_vertices; ++j) {
            min = std::min(min, dist[i][j]);
        }
    }
    
    return min;
}
