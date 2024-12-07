//
//  tsp_heuristic.cpp
//  stanford
//
//  Created by Murat Karaca on 12/7/24.
// 2147483647

#include "tsp_heuristic.h"
#include <unordered_set>

const double INF_VAL = std::numeric_limits<double>::infinity();

double get_euclidian_distance(std::vector<City>& points, int j, int k){
    City j_point = points[j];
    City k_point = points[k];
    return std::sqrt(std::pow(k_point.x - j_point.x, 2) + std::pow(k_point.y - j_point.y, 2));
}

int tsp_heuristic(std::ifstream& file){
    int number_of_cities;
    file >> number_of_cities;
    std::vector<City> cities(number_of_cities + 1);
    for(int i = 1;i<=number_of_cities;i++){
        int index;
        file >> index;
        double x,y;
        file >> x >> y;
        cities[index] = {x,y};
    }
    
    std::unordered_set<int> visited;
    visited.insert(1);
    int current_city = 1;
    double travelling_cost = 0;
    
    while(visited.size() != number_of_cities){
        double closest_distance = INF_VAL;
        int closest_current_city = -1;
        
        for(int i = 2;i<=number_of_cities;i++){
            if(!visited.contains(i)){
                double distance = get_euclidian_distance(cities, current_city, i);
                if (distance < closest_distance ||
                    (distance == closest_distance && i < closest_current_city)) {
                    closest_distance = distance;
                    closest_current_city = i;
                }
            }
        }
        current_city = closest_current_city;
        travelling_cost += closest_distance;
        visited.insert(closest_current_city);
    }
    
    double last_travel = get_euclidian_distance(cities, 1, current_city);
    double val = last_travel + travelling_cost;
    return std::floor(val);
}
