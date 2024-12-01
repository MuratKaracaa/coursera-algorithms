//
//  bellman_ford.cpp
//  stanford
//
//  Created by Murat Karaca on 12/1/24.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <climits>
#include "bellman_ford.h"

int bellman_ford(std::ifstream& file) {
    int number_of_vertices, number_of_edges;
    file >> number_of_vertices >> number_of_edges;

    std::vector<BellmanEdge> edges;
    std::vector<int> distance(number_of_vertices, INT_MAX);

    for (int i = 0; i < number_of_edges; i++) {
        int u, v, weight;
        file >> u >> v >> weight;
        edges.push_back({u - 1, v - 1, weight});
    }

    distance[0] = 0;

    for (int i = 0; i < number_of_vertices - 1; i++) {
        for (const auto& edge : edges) {
            if (distance[edge.u] != INT_MAX && distance[edge.u] + edge.weight < distance[edge.v]) {
                distance[edge.v] = distance[edge.u] + edge.weight;
            }
        }
    }

    for (const auto& edge : edges) {
        if (distance[edge.u] != INT_MAX && distance[edge.u] + edge.weight < distance[edge.v]) {
            std::cerr << "Graph contains a negative-weight cycle\n";
            return -1;
        }
    }
    

    return distance[number_of_vertices - 1];
}

