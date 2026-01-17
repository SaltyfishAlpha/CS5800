#include "../../leetcode_runner.h"
#include "solution.cpp"
#include <vector>
#include <string>

using namespace std;

LEETCODE_MAIN_BEGIN("separate-squares-I", "input4.txt")
    //////// Testcase generation /////////////////
    // srand(0);
    // int n = 5 * 10000;
    // vector<vector<int>> squares;
    // while (n--) {
    //     int x = rand() % 1000000000;
    //     int y = rand() % 1000000000;
    //     int li = rand() % 1000000000;
    //     li = li == 0 ? 1 : li;
    //
    //     squares.push_back({x, y, li});
    // }
    // vector<string> lines;
    // lines.push_back(leetcode::toString(squares));
    // leetcode::writeTestcaseFile("separate-squares-I", "input3.txt",
    //     lines);


    ////////////// INPUT PARSING ///////////////
    // INPUT
    string line;
    getline(cin, line);
    vector<vector<int>> squares = leetcode::parseInt2DVector(line);

    // SOLVE
    leetcode::ScopedTimer timer("separate-squares-I");
    double result = solution.separateSquares1(squares);

    // OUTPUT
    cout<<result<<endl;
LEETCODE_MAIN_END
