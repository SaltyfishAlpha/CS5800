#include <algorithm>
#include <map>

#include "../../leetcode_runner.h"
#include "solution.cpp"
#include <vector>
#include <string>

using namespace std;

LEETCODE_MAIN_BEGIN("problem215")
    string line;
    getline(cin, line);
    vector<int> nums = leetcode::parseIntVector(line);
    getline(cin, line);
    int k = stoi(line);

    leetcode::ScopedTimer timer("k-th value");
    auto result = solution.findKthLargest(nums, k);
    leetcode::printValue(result);
LEETCODE_MAIN_END
