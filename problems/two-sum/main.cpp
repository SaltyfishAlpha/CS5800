#include "../../leetcode_runner.h"
#include "solution.cpp"
#include <vector>
#include <string>

using namespace std;

LEETCODE_MAIN_BEGIN("two-sum", "input2.txt")
    // INPUT: Parse input from file
    string line;
    getline(cin, line);
    vector<int> nums = leetcode::parseIntVector(line);
    getline(cin, line);
    int target = stoi(line);
    
    // SOLVE: Call solution method
    vector<int> result = solution.twoSum(nums, target);
    
    // OUTPUT: Print result
    leetcode::printVector(result);
LEETCODE_MAIN_END
