#include "../../leetcode_runner.h"
#include "solution.cpp"
#include <vector>
#include <string>

using namespace std;

LEETCODE_MAIN_BEGIN("separate-squares-II", "input4.txt")
    // INPUT
    string line;
    getline(cin, line);
    vector<vector<int>> squares = leetcode::parseInt2DVector(line);

    // SOLVE
    leetcode::ScopedTimer timer("separate-squares-II");
    double result = solution.separateSquares(squares);
    
    // OUTPUT
    cout<<result<<endl;
LEETCODE_MAIN_END
