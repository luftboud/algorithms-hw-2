#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>

struct Training {
    std::string name;
    int start;
    int end;
};

std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> result;
    std::string token;
    std::stringstream ss(s);

    while (std::getline(ss, token, delim)) {
        result.push_back(token);
    }

    return result;
}

int max_n_sessions(int T, std::vector<Training> ts) {
    int result = 0;

    std::sort(ts.begin(), ts.end(), [](const Training& x, const Training& y) {
        if (x.end != y.end) return x.end < y.end;
        return x.start < y.start;
    });


    int last_end = -1000000000;
    for (const Training& tr : ts) {

        if (tr.start >= last_end + T) {
            last_end = tr.end;
            result++;
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

    int T;
    if (!(iss >> T)) {
        std::cerr << "Invalid input: first token must be integer K\n";
        return 1;
    }

    std::vector<Training> tr;
    std::string token;

    while (iss >> token) {
        std::vector<std::string> divided = split(token, ':');
        std::vector<std::string> timeslot = split(divided[1], '-');

        Training t;
        t.name = divided[0];
        t.start = std::stoi(timeslot[0]);
        t.end = std::stoi(timeslot[1]);

        tr.push_back(t);
    }

    int res = max_n_sessions(T, tr);
    std::cout << res << std::endl;

    return 0;
}