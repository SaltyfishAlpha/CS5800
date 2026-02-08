#include "../../leetcode_runner.h"
#include "solution.cpp"
#include <vector>
#include <string>

using namespace std;

LEETCODE_MAIN_BEGIN("SparseSet")
    string line;
    getline(cin, line);
    vector<int> nums = leetcode::parseIntVector(line);
    Solution::SparseSetTest(nums);

    Solution::SparseSetLoadTest(1e5);
    Solution::VectorLoadTest(1e5);
LEETCODE_MAIN_END
