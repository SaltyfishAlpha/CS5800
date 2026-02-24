#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int pre = 1, suff = 1;
        int ans = -1e9;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            if (!pre) pre = 1;
            if (!suff) suff = 1;
            pre = pre * nums[i];
            suff = suff * nums[n - i - 1];
            ans = max({ans, pre, suff});
        }

        return ans;
    }
};