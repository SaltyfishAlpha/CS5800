#include "../../leetcode_runner.h"
#include "solution.cpp"
#include <vector>
#include <string>

using namespace std;

LEETCODE_MAIN_BEGIN("p152")
    string line;
    getline(cin, line);
    vector<int> nums = leetcode::parseIntVector(line);

    // Optional: Add Timer to calculate time-use
    leetcode::ScopedTimer timer("Maximum Product Subarray");

    // SOLVE: Call solution method
    int result = solution.maxProduct(nums);
    
    // OUTPUT: Print result
    leetcode::printValue(result);
LEETCODE_MAIN_END
