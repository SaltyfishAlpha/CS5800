#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(),
            [](vector<int>& a, vector<int>& b) { return a[0] < b[0]; });
        int st = intervals[0][0];
        int ed = intervals[0][1];
        vector<vector<int>> result;
        for (auto interval : intervals)
        {
            if (interval[0] > ed)
            {
                result.push_back({st, ed});
                st = interval[0];
                ed = interval[1];
            } else if (interval[0] <= ed)
            {
                ed = max(ed, interval[1]);
            }
        }
        result.push_back({st, ed});
        return result;
    }
};
