#include "../../leetcode_runner.h"
#include "solution.cpp"
#include <vector>
#include <string>

using namespace std;

LEETCODE_MAIN_BEGIN("Sort-List-148", "input2.txt")
    string line;
    getline(cin, line);
    vector<int> nums = leetcode::parseIntVector(line);
    ListNode *head;
    if (nums.size() == 0) head = nullptr;
    else
    {
        head = new ListNode(nums[0]);
        auto tp = head;
        for (auto itr = nums.begin()+1; itr != nums.end(); ++itr)
        {
            tp->next = new ListNode(*itr);
            tp = tp->next;
        }
    }

    // Optional: Add Timer to calculate time-use
    auto *timer = new leetcode::ScopedTimer ("Problem Name Here");

    // SOLVE: Call solution method
    // Example:
    ListNode *result = solution.sortList(head);

    delete timer;

    // OUTPUT: Print result
    if (result == nullptr) cout<<"[]";
    else
        for (auto tp = result; tp != nullptr; tp = tp->next)
        {
            cout<<tp->val<<",";
        }
LEETCODE_MAIN_END
