#include <string>
#include <vector>
#include <iostream>
#include <sstream>

int INF = 1000000000;
int count_tiles(int N, std::vector<int>& tiles) {
    std::vector<int> dp(N+1, INF);
    dp[0] = 0;

    for (const int t : tiles) {
        for (int s = N; s >= t; s--) {
            if (dp[s - t] != INF) {
                dp[s] = std::min(dp[s], dp[s-t] +1);
            }
        }
    }
    if (dp[N] == INF) {
        return -1;
    }
    return dp[N];
}

int main(){
    std::string line;
    if (!std::getline(std::cin, line)) {
        std::cerr << "No input\n";
        return 1;
    }

    std::istringstream iss(line);

    int N;
    if (!(iss >> N)) {
        std::cerr << "Invalid input: first token must be integer N\n";
        return 1;
    }

    std::vector<int> tiles;
    int tile;

    while (iss >> tile) {
        if (tile <= 0) {
            std::cerr << "Invalid tile size: must be positive\n";
            return 1;
        }
        tiles.push_back(tile);
    }

    int res = count_tiles(N, tiles);
    std::cout << res << std::endl;

    return 0;
}