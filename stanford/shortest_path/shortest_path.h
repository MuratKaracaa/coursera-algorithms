//
//  shortest_path.h
//  stanford
//
//  Created by Murat Karaca on 11/16/24.
//

#include <vector>
#include <string>

struct EdgeWithWeight {
    int v;
    int w;
    int weight;
};

std::string get_shortest_path(std::vector<EdgeWithWeight>& edges);
