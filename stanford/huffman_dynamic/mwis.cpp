//
//  mwis.cpp
//  stanford
//
//  Created by Murat Karaca on 11/29/24.
//

#include "mwis.h"
#include <unordered_set>
#include <iostream>

void mwis(std::ifstream& file){
    int number_of_vertices;
    file >> number_of_vertices;
    std::vector<long long> A(number_of_vertices + 1);
    std::vector<int> weights(number_of_vertices + 1);
    std::unordered_set<int> path;
    
    A[0] = 0;
    
    for(int i = 1;i<=number_of_vertices;i++){
        int weight;
        file >> weight;
        weights[i] = weight;
        if(i == 1){
            A[i] = weight;
        } else {
            long long oneBefore = A[i-1];
            long long twoBefore = A[i-2] + weight;
            A[i] = std::max(oneBefore, twoBefore);
        }
    }
    
    int n = number_of_vertices;
    
    while(n >= 1){
        if(n==1){
            long long oneAfter = A[n+1];
            long long twoAfter = A[n+2] + weights[n];
            if(twoAfter>oneAfter){
                path.insert(n);
            }
            n--;
        } else if(A[n-1] >= A[n-2] + weights[n]){
            n--;
        } else {
            path.insert(n);
            n = n-2;
        }
    }
    
    std::vector<int> targets = {1, 2, 3, 4, 17, 117, 517, 997};
    std::string res = "";
    
    for(int target: targets){
        if(path.contains(target)){
            res += "1";
        } else {
            res += "0";
        }
    }
    
    std::cout << res << "\n";

}
