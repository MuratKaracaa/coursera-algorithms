//
//  tsp.cpp
//  stanford
//
//  Created by Murat Karaca on 12/6/24.
// 26442

#include "tsp.h"
#include <unordered_set>
#include <sstream>

const float INF = std::numeric_limits<float>::infinity();

float get_euclidian_distance(std::vector<Point>& points, int j, int k){
    Point j_point = points[j];
    Point k_point = points[k];
    return std::sqrt(std::pow(k_point.x - j_point.x, 2) + std::pow(k_point.y - j_point.y, 2));
}

int tsp(std::ifstream& file) {
    int number_of_vertices;
    file >> number_of_vertices;
    int n = number_of_vertices;

    std::vector<Point> points(n);
    for (int i = 0; i < n; i++) {
        float x, y;
        file >> x >> y;
        points[i] = {x, y};
    }

    std::vector<std::vector<float>> dist(n, std::vector<float>(n, 0.0f));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = get_euclidian_distance(points, i, j);
        }
    }

    std::vector<std::vector<float>> A(1 << n, std::vector<float>(n, INF));

    A[1][0] = 0.0f;

    for (int m = 2; m <= n; m++) {
        for (int mask = 0; mask < (1 << n); mask++) {
            if ((mask & 1) == 0) continue;
            if (__builtin_popcount(mask) != m) continue;

            for (int j = 1; j < n; j++) {
                if (!(mask & (1 << j))) continue;
                int prevMask = mask ^ (1 << j);
                float best_value = INF;

                for (int k = 0; k < n; k++) {
                    if (k == j) continue;
                    if (!(prevMask & (1 << k))) continue;
                    float candidate = A[prevMask][k] + dist[k][j];
                    if (candidate < best_value) {
                        best_value = candidate;
                    }
                }

                A[mask][j] = best_value;
            }
        }
    }

    int fullMask = (1 << n) - 1;
    float best_value = INF;
    for (int j = 1; j < n; j++) {
        float candidate = A[fullMask][j] + dist[j][0];
        if (candidate < best_value) {
            best_value = candidate;
        }
    }

    return best_value;
}
