#include <algorithm>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
public:
    int maximizeSquareHoleArea(int n, int m, vector<int>& hBars, vector<int>& vBars) {

        sort(hBars.begin(), hBars.end());
        sort(vBars.begin(), vBars.end());

        // leetcode::printVector(hBars); cout<<"\n";
        // leetcode::printVector(vBars); cout<<"\n";

        int maxLen_h = 1;
        int maxLen_v = 1;
        int tmp = 1;
        for (auto i = hBars.begin() + 1; i != hBars.end(); ++i)
        {
            if (*i == *(i-1) + 1) tmp++;
            else
            {
                maxLen_h = max(maxLen_h, tmp);
                tmp = 1;
            }
        }
        maxLen_h = max(maxLen_h, tmp);

        tmp = 1;
        for (auto i = vBars.begin() + 1; i != vBars.end(); ++i)
        {
            if (*i == *(i-1) + 1) tmp++;
            else
            {
                maxLen_v = max(maxLen_v, tmp);
                tmp = 1;
            }
        }
        maxLen_v = max(maxLen_v, tmp);

        int result = min(maxLen_h, maxLen_v) + 1;
        return result * result;
    }
};