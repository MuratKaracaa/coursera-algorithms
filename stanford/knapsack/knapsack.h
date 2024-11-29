//
//  knapsack.h
//  stanford
//
//  Created by Murat Karaca on 11/29/24.
//

#include <fstream>

struct Item {
    int value;
    int weight;
};

int knapsack(std::ifstream& file);
