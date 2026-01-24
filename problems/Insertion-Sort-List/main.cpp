#include "../../leetcode_runner.h"
#include "solution.cpp"
#include <vector>
#include <string>

using namespace std;

LEETCODE_MAIN_BEGIN("Insertion-Sort-List", "input2.txt")
    string line;
    getline(cin, line);
    vector<int> nums = leetcode::parseIntVector(line);

    ListNode *head = new ListNode(nums[0]);
    for (auto itr = nums.begin()+1; itr != nums.end(); ++itr)
    {
        solution.insertNode(*head, *itr);
    }

    // Optional: Add Timer to calculate time-use
    auto *timer = new leetcode::ScopedTimer ("Problem Name Here");

    // SOLVE: Call solution method
    // Example:
    ListNode *result = solution.insertionSortList(head);

    delete timer;

    // OUTPUT: Print result
    for (auto tp = result; tp != nullptr; tp = tp->next)
    {
        cout<<tp->val<<",";
    }
LEETCODE_MAIN_END
