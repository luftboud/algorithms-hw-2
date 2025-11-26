#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <unordered_set>

std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> result;
    std::string token;
    std::stringstream ss(s);

    while (std::getline(ss, token, delim)) {
        result.push_back(token);
    }

    return result;
}


int count_workers(const std::string& s) {
    int result = 0;

    std::istringstream iss(s);
    std::vector<std::string> projects;
    std::string p;

    while (iss >> p) {
        //pushing each project into the vector
        projects.push_back(p);
    }

    if (projects.empty()) {
        throw std::invalid_argument("count_workers: empty input string");
    }

    int K = std::stoi(projects[0]); //K
    projects.erase(projects.begin()); // deleting it

    std::map<std::string, int> jobs; // here we count n of projects for each worker

    for (std::string& project : projects) {
        std::vector<std::string> divided = split(project, ':');

        if (divided.size() < 2) continue;
        std::string& workers_str = divided[1];
        if (workers_str.empty()) continue;

        //vector of workers for this project
        std::vector<std::string> workers = split(workers_str, ',');

        std::unordered_set<std::string> unique_workers; // so we don't duplicate
        for (const auto& w : workers) {
            if (!w.empty()) {
                unique_workers.insert(w);
            }
        }

        for (const auto& w : unique_workers) {
            int& j = jobs[w];
            j++;
            if (j == K + 1) {
                result++;
            }
        }
    }
    return result;
}

int main(){
//    std::string s = "2 web:1,2,3 mobile:2,3,4 api:1,2,5 database:3,4,5";
    std::string s = "1 alpha:1,1";
//    std::string s = "1 core:10,20,30 ui:20,30,40 devops:30,40,50 data:10,30,50";
    int res = count_workers(s);
    std::cout << res<< std::endl;

    return 0;
}