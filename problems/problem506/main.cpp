#include <algorithm>
#include <map>

#include "../../leetcode_runner.h"
#include "solution.cpp"
#include <vector>
#include <string>

using namespace std;
using namespace problem506;

LEETCODE_MAIN_BEGIN("problem506")
    string line;
    getline(cin, line);
    vector<int> nums = leetcode::parseIntVector(line);

    auto result = solution.findRelativeRanks(nums);
    leetcode::printVector(result);
LEETCODE_MAIN_END
