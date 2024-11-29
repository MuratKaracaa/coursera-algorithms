//
//  knapsack.cpp
//  stanford
//
//  Created by Murat Karaca on 11/29/24.
//

#include "knapsack.h"
// 2493893
int knapsack(std::ifstream& file){
    int size;
    int number_of_items;
    file >> size >> number_of_items;
    std::vector<int> values;
    std::vector<int> weights;
    
    std::vector<std::vector<int>> A(number_of_items + 1, std::vector<int>(size+ 1, 0));

    
    for(int i = 0;i<number_of_items;i++){
        int value;
        int weight;
        file >> value >> weight;
        values.push_back(value);
        weights.push_back(weight);
    }
    
    for(int i = 1;i<=number_of_items;i++){
        for(int j = 1;j<=size;j++){
            if(weights[i-1] > j){
                A[i][j] = A[i-1][j];
            } else {
                A[i][j] = std::max(A[i - 1][j], A[i - 1][j - weights[i - 1]] + values[i - 1]);
            }
        }
    }
    
    return A[number_of_items][size];
}
