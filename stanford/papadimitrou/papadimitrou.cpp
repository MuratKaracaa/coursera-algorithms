//
//  papadimitrou.cpp
//  stanford
//
//  Created by Murat Karaca on 12/17/24.
//

#include "papadimitrou.h"
#include <cmath>
#include <random>
#include <unordered_set>

#include <iostream>
#include <unordered_set>
#include <random>

int getRandomElement(const std::unordered_set<int>& mySet, std::mt19937& gen) {
    if (mySet.empty()) {
        throw std::runtime_error("The set is empty, cannot select a random element.");
    }

    std::uniform_int_distribution<> dist(0, mySet.size() - 1);

    int randomIndex = dist(gen);

    auto it = mySet.begin();
    std::advance(it, randomIndex);

    return *it;
}

int getRandomElementFromPair(const std::pair<int, int>& myPair, std::mt19937& gen) {
    std::uniform_int_distribution<> dist(0, 1);
    return (dist(gen) == 0) ? myPair.first : myPair.second;
}

bool get_is_clauses_satisfied(std::vector<std::pair<int,int>>& clauses, std::vector<bool>& assignments, int& number_of_items, std::unordered_set<int>& satisfied_indices_set, std::unordered_set<int>& unsatisfied_indices_set){
    satisfied_indices_set.clear();
    unsatisfied_indices_set.clear();
    
    for(int i = 1;i<=number_of_items;i++){
        std::pair<int,int> clause = clauses[i];
        bool first_bool_value = clause.first > 0 ? assignments[clause.first] : !assignments[-clause.first];
        bool second_bool_value = clause.second > 0 ? assignments[clause.second] : !assignments[-clause.second];
        
        if(!(first_bool_value || second_bool_value)){
            unsatisfied_indices_set.insert(i);
        } else {
            satisfied_indices_set.insert(i);
        }
    }
    
    return satisfied_indices_set.size() == number_of_items;
}

int papadimitrou_naive(std::ifstream& file){
    int number_of_items;
    file >> number_of_items;
    
    std::vector<std::pair<int,int>> clauses(number_of_items+1);
    
    for(int i = 1;i<=number_of_items;i++){
        int first;
        int second;
        file >> first >> second;
        clauses[i] = {first, second};
    }
    
    int outer_for_loop_iteration_count = log2(number_of_items);
    int inner_for_loop_iteration_count = pow(number_of_items, 2);
    for(int i = 0;i<outer_for_loop_iteration_count;i++){
        std::vector<bool> random_assignments(number_of_items + 1);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::bernoulli_distribution dist(0.5);
        for (int k = 0; k <= number_of_items; k++) {
            random_assignments[k] = dist(gen);
        }
        
        std::unordered_set<int> satisfied_indices_set;
        std::unordered_set<int> unsatisfied_indices_set;
        
        for(int l = 1;l<=number_of_items;l++){
            std::pair<int,int> clause = clauses[l];
            bool first_bool_value = clause.first > 0 ? random_assignments[clause.first] : !random_assignments[-clause.first];
            bool second_bool_value = clause.second > 0 ? random_assignments[clause.second] : !random_assignments[-clause.second];
            bool is_satisfied = first_bool_value || second_bool_value;
            if(is_satisfied){
                satisfied_indices_set.insert(l);
            } else {
                unsatisfied_indices_set.insert(l);
            }
        }
        
        for(int j = 0;j<inner_for_loop_iteration_count;j++){
            bool is_satisfied = get_is_clauses_satisfied(clauses, random_assignments, number_of_items, satisfied_indices_set, unsatisfied_indices_set);
            if(is_satisfied){
                return 1;
            } else {
                int random_item_index = getRandomElement(unsatisfied_indices_set, gen);
                unsatisfied_indices_set.erase(random_item_index);
                satisfied_indices_set.insert(random_item_index);
                std::pair<int,int> random_element = clauses[random_item_index];
                int random_element_from_pair = getRandomElementFromPair(random_element, gen);
                random_assignments[random_element_from_pair] = !random_assignments[random_element_from_pair];
            }
        }
    }
    
    return 0;
}

struct pair_hash {
    size_t operator()(const std::pair<int,int>& p) const {
        auto h1 = std::hash<int>()(p.first);
        auto h2 = std::hash<int>()(p.second);
        return h1 ^ (h2 + 0x9e3779b97f4a7c15ULL + (h1 << 6) + (h1 >> 2));
    }
};

std::pair<int,int> canonicalClause(int a, int b) {
    std::array<int,2> arr = {a, b};
    std::sort(arr.begin(), arr.end(), [](int x, int y){
        if (abs(x) == abs(y)) {
            return x < y;
        }
        return abs(x) < abs(y);
    });
    return {arr[0], arr[1]};
}

int papadimitrou(std::ifstream& file){
    int number_of_items;
    file >> number_of_items;
    
    std::unordered_set<std::pair<int,int>, pair_hash> seenClauses;
    std::vector<std::pair<int,int>> clauses;
    std::unordered_map<int, std::vector<int>> index_map;
    
    for (int i = 0; i < number_of_items; i++) {
        int first, second;
        file >> first >> second;
        auto c = canonicalClause(first, second);
        if (!seenClauses.contains(c)) {
            seenClauses.insert(c);
            int clauseIndex = static_cast<int>(clauses.size());
            clauses.push_back(c);

            index_map[c.first].push_back(clauseIndex);
            index_map[c.second].push_back(clauseIndex);
        }
    }
    
    int clause_size = clauses.size();
    
    int outer_for_loop_iteration_count = log2(clause_size);
    int inner_for_loop_iteration_count = pow(clause_size, 2);
    
    std::random_device rd;
    
    for(int i = 0;i<outer_for_loop_iteration_count;i++){
        std::vector<bool> random_assignments(number_of_items + 1);
        std::mt19937 gen(rd());
        std::bernoulli_distribution dist(0.5);
        for (int k = 1; k <= number_of_items; k++) {
            random_assignments[k] = dist(gen);
        }
        
        std::unordered_set<int> satisfied_indices_set;
        std::unordered_set<int> unsatisfied_indices_set;
        
        for(int l = 0;l<clause_size;l++){
            std::pair<int,int> clause = clauses[l];
            bool first_bool_value = clause.first > 0 ? random_assignments[clause.first] : !random_assignments[-clause.first];
            bool second_bool_value = clause.second > 0 ? random_assignments[clause.second] : !random_assignments[-clause.second];
            bool is_satisfied = first_bool_value || second_bool_value;
            if(is_satisfied){
                satisfied_indices_set.insert(l);
            } else {
                unsatisfied_indices_set.insert(l);
            }
        }
        
        
        for(int j = 0;j<inner_for_loop_iteration_count;j++){
            if(unsatisfied_indices_set.empty()){
                return 1;
            }
            
            int random_item_index = getRandomElement(unsatisfied_indices_set, gen);
            unsatisfied_indices_set.erase(random_item_index);
            satisfied_indices_set.insert(random_item_index);
            std::pair<int,int> random_element = clauses[random_item_index];
            int random_element_from_pair = getRandomElementFromPair(random_element, gen);
            int varIndex = std::abs(random_element_from_pair);
            random_assignments[varIndex] = !random_assignments[varIndex];
            
            std::vector<int> affectedClausesPos = index_map[varIndex];
            std::vector<int> affectedClausesNeg = index_map[-varIndex];
            
            auto recheckClause = [&](int cIndex){
                const auto &cl = clauses[cIndex];
                bool fb = (cl.first > 0) ? random_assignments[cl.first] : !random_assignments[-cl.first];
                bool sb = (cl.second > 0)? random_assignments[cl.second]: !random_assignments[-cl.second];
                bool nowSatisfied = (fb || sb);

                if(nowSatisfied){
                    unsatisfied_indices_set.erase(cIndex);
                    satisfied_indices_set.insert(cIndex);
                } else {
                    satisfied_indices_set.erase(cIndex);
                    unsatisfied_indices_set.insert(cIndex);
                }
            };

            
            for(int cIdx : affectedClausesPos) {
                recheckClause(cIdx);
            }
            
            for(int cIdx : affectedClausesNeg) {
                recheckClause(cIdx);
            }
            
        }
    }
    
    return 0;
}
