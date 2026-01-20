#include "../../leetcode_runner.h"
#include "solution.cpp"
#include <vector>
#include <string>

using namespace std;

LEETCODE_MAIN_BEGIN("Maximum-Side-Length-1292", "input3.txt")
    string line;

    getline(cin, line);
    vector<vector<int>> mat = leetcode::parseInt2DVector(line);

    getline(cin, line);
    int threshold = stoi(line);

    leetcode::ScopedTimer timer("Maximum-Side-Length-1292");

    int result = solution.maxSideLength(mat, threshold);

    cout<<result<<endl;
LEETCODE_MAIN_END
