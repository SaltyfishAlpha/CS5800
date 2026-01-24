#include <algorithm>

#include "../../leetcode_runner.h"
#include "solution.cpp"
#include <vector>
#include <string>

using namespace std;

LEETCODE_MAIN_BEGIN("sort", "input.txt")
    // srand(1);
    // int len = rand()%100;
    // vector<int> output;
    // while(len--)
    // {
    //     output.push_back(rand()%100);
    // }
    // vector<string> lines;
    // lines.push_back(leetcode::toString(output));
    // leetcode::writeTestcaseFile("sort", "input.txt", lines);


    string line;
    getline(cin, line);
    vector<int> arr = leetcode::parseIntVector(line);
    vector<int> ans(arr.begin(), arr.end());


    auto timer1 = new leetcode::ScopedTimer("STD Sort");
    sort(ans.begin(), ans.end());
    delete timer1;

    auto timer2 = new leetcode::ScopedTimer("Merge Sort");
    vector<int> result = solution.mergeSort(arr);
    delete timer2;

    leetcode::printVector(result); cout<<endl;
    leetcode::printVector(ans); cout<<endl;



LEETCODE_MAIN_END
