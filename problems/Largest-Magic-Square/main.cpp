#include "../../leetcode_runner.h"
#include "solution.cpp"
#include <vector>
#include <string>

using namespace std;

LEETCODE_MAIN_BEGIN("Largest-Magic-Square", "input1.txt")
    string line;
    getline(cin, line);
    vector<vector<int>> grid = leetcode::parseInt2DVector(line);;

    leetcode::ScopedTimer timer("Largest-Magic-Square");

    int result = solution.largestMagicSquare(grid);

    cout<<result<<endl;
LEETCODE_MAIN_END
