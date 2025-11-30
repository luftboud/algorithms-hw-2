#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>

std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> result;
    std::string token;
    std::stringstream ss(s);

    while (std::getline(ss, token, delim)) {
        result.push_back(token);
    }

    return result;
}

int count_workers(int K, const std::vector<std::string>& projects) {
    int result = 0;

    std::unordered_map<std::string, int> jobs; // here we count n of projects for each worker

    for (const std::string& project : projects) {
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
    std::string line;
    if (!std::getline(std::cin, line)) {
        std::cerr << "No input\n";
        return 1;
    }

    std::istringstream iss(line);

    int K;
    if (!(iss >> K)) {
        std::cerr << "Invalid input: first token must be integer K\n";
        return 1;
    }

    std::vector<std::string> projects;
    std::string token;

    while (iss >> token) {
        projects.push_back(token);
    }

    int res = count_workers(K, projects);
    std::cout << res << std::endl;

    return 0;
}