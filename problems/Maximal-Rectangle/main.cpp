#include "../../leetcode_runner.h"
#include "solution.cpp"
#include <vector>
#include <string>

using namespace std;

LEETCODE_MAIN_BEGIN("Maximal-Rectangle")
    string line;
    getline(cin, line);
    vector<vector<char>> matrix = leetcode::parseChar2DVector(line);

    leetcode::ScopedTimer timer("Maximal-Rectangle");

    int result = solution.maximalRectangle(matrix);

    cout<<result<<endl;
LEETCODE_MAIN_END
