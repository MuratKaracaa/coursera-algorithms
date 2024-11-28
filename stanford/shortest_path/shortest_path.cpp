//
//  shortest_path.cpp
//  stanford
//
//  Created by Murat Karaca on 11/16/24.
//

#include "shortest_path.h"
#include <queue>
#include <sstream>
#include <set>
#include <algorithm>

// TODO refactor this to use priority queue instead
// in the input file, each line, first one is vertex key, subsequent numbers are key,weight format
std::string get_shortest_path(std::vector<EdgeWithWeight>& edges) {
    std::vector<int> distances(200);
    for(int i = 0;i<distances.size();i++){
        if(i == 0){
            distances[i] = 0;
        } else {
            distances[i] = INT_MAX;
        }
    }
    std::set<int> X;
    X.insert(0);
    
    while(X.size() != 200){
        int currentSmallest = INT_MAX;
        EdgeWithWeight currentV;
        
        for(EdgeWithWeight edge: edges){
            if(X.contains(edge.v) && !X.contains(edge.w) && distances[edge.v] + edge.weight < currentSmallest){
                currentSmallest = distances[edge.v] + edge.weight;
                currentV = edge;
            }
        }
        
        X.insert(currentV.w);
        distances[currentV.w] = distances[currentV.v] + currentV.weight;
        
    }
    std::ostringstream oss;
    std::vector<int> targets = {7,37,59,82,99,115,133,165,188,197};
    
    for(int target: targets){
        oss << distances[target - 1] << ",";
    }

    return oss.str();
}
