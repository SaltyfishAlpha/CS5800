#include "../../leetcode_runner.h"
#include "solution.cpp"
#include <vector>
#include <string>

using namespace std;

LEETCODE_MAIN_BEGIN("Find-the-Largest-Area-3047", "input2.txt")
    string line;
    getline(cin, line);
    vector<vector<int>> bottomLeft = leetcode::parseInt2DVector(line);
    getline(cin, line);
    vector<vector<int>> topRight = leetcode::parseInt2DVector(line);

    leetcode::ScopedTimer timer("Find-the-Largest-Area-3047");

    // SOLVE: Call solution method
    long long result = solution.largestSquareArea(bottomLeft, topRight);
    
    // OUTPUT: Print result
    cout<<result<<endl;
LEETCODE_MAIN_END
