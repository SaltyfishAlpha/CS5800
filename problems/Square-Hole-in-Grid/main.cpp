#include "../../leetcode_runner.h"
#include "solution.cpp"
#include <vector>
#include <string>

using namespace std;

LEETCODE_MAIN_BEGIN("Square-Hole-in-Grid", "input3.txt")
    string line;

    getline(cin, line);
    int n = stoi(line);

    getline(cin, line);
    int m = stoi(line);

    getline(cin, line);
    vector<int> hBars = leetcode::parseIntVector(line);

    getline(cin, line);
    vector<int> vBars = leetcode::parseIntVector(line);

    leetcode::ScopedTimer timer("Removing-Fences");

    int result = solution.maximizeSquareHoleArea(n, m, hBars, vBars);

    cout<<result<<endl;
LEETCODE_MAIN_END
