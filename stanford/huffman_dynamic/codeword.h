//
//  codeword.h
//  stanford
//
//  Created by Murat Karaca on 11/28/24.
//

#include <fstream>

struct TreeNode {
    std::string key;
    std::string left;
    std::string right;
    long long weight;
};

int codeword(std::ifstream& file);
