#include "../../leetcode_runner.h"
#include "solution.cpp"
#include <vector>
#include <string>

using namespace std;

LEETCODE_MAIN_BEGIN("Removing-Fences", "input4.txt")
    string line;

    getline(cin, line);
    int m = stoi(line);

    getline(cin, line);
    int n = stoi(line);

    getline(cin, line);
    vector<int> hFences = leetcode::parseIntVector(line);

    getline(cin, line);
    vector<int> vFences = leetcode::parseIntVector(line);

    leetcode::ScopedTimer timer("Removing-Fences");

    int result = solution.maximizeSquareArea(m, n, hFences, vFences);

    cout<<result<<endl;
LEETCODE_MAIN_END
