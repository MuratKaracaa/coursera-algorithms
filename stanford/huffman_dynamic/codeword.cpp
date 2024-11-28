//
//  codeword.cpp
//  stanford
//
//  Created by Murat Karaca on 11/28/24.
//

#include "codeword.h"
#include <vector>
#include <queue>
#include <iostream>

struct Comp {
    bool operator()(const TreeNode& first, const TreeNode& second) const {
        return first.weight > second.weight;
    }
};

int dfs(std::unordered_map<std::string, TreeNode>& tree, TreeNode& root){
    if(root.left == "" && root.right == ""){
        return 0;
    } else {
        int left = 0;
        int right = 0;
        if(root.left != ""){
            left = dfs(tree, tree[root.left]);
        }
        if(root.right != ""){
            right = dfs(tree,tree[root.right]);
        }
        return 1 + std::max(left, right);
        
    }
}

int bfs(std::unordered_map<std::string, TreeNode>& tree, TreeNode& root){
    int smallest = 0;
    
    std::queue<TreeNode> bfs_queue;
    
    bfs_queue.push(root);
    while(!bfs_queue.empty()){
        int size = bfs_queue.size();
        for(int i = 0;i<size;i++){
            TreeNode next = bfs_queue.front();
            if(next.left == "" && next.right == ""){
                return smallest;
            }
            bfs_queue.pop();
            if(next.left != ""){
                bfs_queue.push(tree[next.left]);
            }
            if(next.right != ""){
                bfs_queue.push(tree[next.right]);
            }
        }
        smallest++;
    }
    
    return smallest;
}

int codeword(std::ifstream& file){
    int number_of_symbols;
    std::priority_queue<TreeNode,std::vector<TreeNode> ,Comp> tree_queue;
    std::unordered_map<std::string, TreeNode> tree;
    
    file >> number_of_symbols;
    for(int i = 0;i<number_of_symbols;i++){
        long weight;
        
        file >> weight;
        tree_queue.push({std::to_string(i),"","",weight});
        std::string node_key = std::to_string(i);
        tree[node_key].key = node_key;
        tree[node_key].left = "";
        tree[node_key].right = "";
        tree[node_key].weight = weight;
    }
    
    while(tree_queue.size() >= 2){
        TreeNode node_first = tree_queue.top();
        tree_queue.pop();
        TreeNode node_second = tree_queue.top();
        tree_queue.pop();
        
        std::string new_key =node_first.key + '-' + node_second.key;
        
        tree_queue.push({new_key,node_first.key, node_second.key,node_first.weight + node_second.weight});
        tree[new_key].key = new_key;
        tree[new_key].left = node_first.key;
        tree[new_key].right = node_second.key;
        tree[new_key].weight = node_first.weight + node_second.weight;
    }
    
    TreeNode root = tree_queue.top();
    
    
    int highest = dfs(tree, root);
    int smallest = bfs(tree, root);

    //9
    std::cout << smallest << "\n";
    //19
    std::cout << highest << "\n";

    
    return 0;
}
