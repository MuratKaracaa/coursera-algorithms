//
//  weighted_sum.cpp
//  stanford
//
//  Created by Murat Karaca on 11/24/24.
//

#include <fstream>

#include <set>

struct Job {
    double weight;
    double length;
    double score;

    Job(double w, double l) : weight(w), length(l), score(w / l) {}
};

struct Comparator {
    bool operator()(const Job& first, const Job& second){
        if(first.score == second.score){
            return first.weight < second.weight;
        } else {
            return first.score < second.score;
        }
    }
};

long long weighted_sum(std::ifstream& file){
    std::priority_queue<Job,std::vector<Job> ,Comparator> job_queue;
    
    int capacity;
    
    file >> capacity;
    
    for(int i = 0;i<capacity;i++){
        double weight, length;
        
        file >> weight >> length;
        job_queue.push({weight, length});
    }
    
    file.close();
    
    long long sum = 0;
    long long current_time_stamp = 0;
    
    while(!job_queue.empty()){
        Job job = job_queue.top();
        job_queue.pop();
        current_time_stamp += job.length;
        sum += current_time_stamp * job.weight;
    }
    
    return sum;
}
