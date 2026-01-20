#include <algorithm>
#include <unordered_set>
#include <vector>
using namespace std;

bool inline check(const vector<vector<int>>& pSum, int size, int threshold, int w, int h)
{
    for (int i = 1; i <= h - size + 1; ++i) {
        for (int j = 1; j <= w - size + 1; ++j)
        {
            int sum = pSum[i+size-1][j+size-1]
                    - pSum[i+size-1][j-1] - pSum[i-1][j+size-1]
                    + pSum[i-1][j-1];
            if (sum <= threshold)
                return true;
        }
    }
    return false;
}

class Solution {
public:
    int maxSideLength(vector<vector<int>>& mat, int threshold) {
        int h = mat.size();
        int w = mat[0].size();
        int n = min(w, h);

        vector pSum(h + 1, vector<int>(w+1));

        for (int i = 1; i <= h; ++i)
            for (int j = 1; j <= w; ++j){
                pSum[i][j] = mat[i-1][j-1] + pSum[i][j-1] + pSum[i-1][j] - pSum[i-1][j-1];
            }

        // binary search
        int l = 0; int r = n;
        int mid = (l+r)>>1;

        while (r-l > 1) {

            if (check(pSum, mid, threshold, w, h))
                l = mid;
            else r = mid;

            mid = (l+r)>>1;
        }

        if (check(pSum, r, threshold, w, h))
            return r;
        return l;
    }
};
