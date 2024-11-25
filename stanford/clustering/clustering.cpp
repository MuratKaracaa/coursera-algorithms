//
//  clustering.cpp
//  stanford
//
//  Created by Murat Karaca on 11/25/24.
//

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

#include "clustering.h"
#include "../disjoint_set/disjoint_set.h"
#include <set>
#include <sstream>
#include <vector>

std::string trim_and_remove_spaces(const std::string& input);

int clustering(std::ifstream& file){
    std::multiset<Edge, Comp> sorted_items;
    int number_of_nodes;
    
    file >> number_of_nodes;
    
    int v, w, length;
    while (file >> v >> w >> length) {
        sorted_items.insert({v - 1, w - 1, length});
    }
    
    file.close();
    
    int cluster_count = number_of_nodes;
    
    disjoint_set clusters = disjoint_set(number_of_nodes);
    
    for(Edge edge: sorted_items){
        if(cluster_count == 4){
            int vParent = clusters.find(edge.v);
            int wParent = clusters.find(edge.w);
            
            if(vParent != wParent){
                return edge.length;
            }
        }
        int vParent = clusters.find(edge.v);
        int wParent = clusters.find(edge.w);
        
        if(vParent == wParent){
            continue;
        } else {
            cluster_count--;
            clusters.unite(vParent, wParent);
        }
    }
    
    
    return 0;

}

int clustering_with_hamming_distance(std::ifstream& file){
    std::multiset<Edge, Comp> sorted_items;
    int number_of_nodes;
    int bit_count;
    
    file >> number_of_nodes >> bit_count;
    
    std::string line;
    std::unordered_map<std::string, int> line_set;
    std::vector<std::string> lines_list;
    
    int node_index = 0;
    for(int i = 0; i <= number_of_nodes; i++){
        getline(file, line);
        std::string trimmed_line = trim_and_remove_spaces(line);
        if(trimmed_line.size() > 0){
            if(!line_set.contains(trimmed_line)){
                line_set[trimmed_line] = node_index;
                lines_list.push_back(trimmed_line);
                node_index++;
            }
        }
    }
    
    file.close();

    for (int index = 0;index<lines_list.size();index++) {
        std::string current = lines_list[index];

        for(int i = 0;i<bit_count;i++){
            std::string temp = current;
            temp[i] = temp[i] == '0' ? '1' : '0';
            if(line_set.contains(temp)){
                sorted_items.insert({index, line_set[temp], 1});
            }
        }
        
        for(int i = 0;i<bit_count-1;i++){
            for(int j = i+1;j<bit_count;j++){
                std::string temp = current;
                temp[i] = temp[i] == '0' ? '1' : '0';
                temp[j] = temp[j] == '0' ? '1' : '0';
                if(line_set.contains(temp)){
                    sorted_items.insert({index, line_set[temp], 2});
                }
            }
        }
    }

    
    disjoint_set clusters = disjoint_set(lines_list.size());
    
    int cluster_count = lines_list.size();

    for(Edge edge: sorted_items){
        int vParent = clusters.find(edge.v);
        int wParent = clusters.find(edge.w);
        
        if(vParent == wParent){
            continue;
        } else {
            cluster_count--;
            clusters.unite(vParent, wParent);
        }
    }
    
    return cluster_count;
}

std::string trim_and_remove_spaces(const std::string& input) {
    std::string result;
    for (char c : input) {
        if (c != ' ') {
            result += c;
        }
    }
    return result;
}
