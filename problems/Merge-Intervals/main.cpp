#include "../../leetcode_runner.h"
#include "solution.cpp"
#include <vector>
#include <string>

using namespace std;

LEETCODE_MAIN_BEGIN("Merge-Intervals", "input1.txt")
    string line;
    getline(cin, line);
    vector<vector<int>> intervals = leetcode::parseInt2DVector(line);

    auto *timer = new leetcode::ScopedTimer ("Problem Name Here");

    auto result = solution.merge(intervals);

    delete timer;

    leetcode::print2DVector(result);
LEETCODE_MAIN_END
