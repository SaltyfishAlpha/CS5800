#include "../../leetcode_runner.h"
#include "solution.cpp"
#include <vector>
#include <string>

using namespace std;

LEETCODE_MAIN_BEGIN("Hanoi")
    string line;
    getline(cin, line);
    int n = leetcode::parseValue<int>(line);

    leetcode::ScopedTimer timer("Towers of Hanoi");

    // SOLVE: Call solution method
    solution.Hanoi(n);
    cout<<endl;
LEETCODE_MAIN_END
