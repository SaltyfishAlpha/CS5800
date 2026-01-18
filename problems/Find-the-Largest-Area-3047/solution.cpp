#include <vector>
using namespace std;

class Solution {
public:

    long long largestSquareArea(vector<vector<int>>& bottomLeft, vector<vector<int>>& topRight) {
        // leetcode::print2DVector(bottomLeft); cout<<"\n";
        // leetcode::print2DVector(topRight); cout<<"\n";

        int size = bottomLeft.size();
        int maxLen = 0;

        for (int i = 0; i < size; ++i)
        {
            for (int j = i+1; j < size; ++j)
            {
                int min_width = min(topRight[i][0], topRight[j][0]) -
                    max(bottomLeft[i][0], bottomLeft[j][0]);

                int min_height = min(topRight[i][1], topRight[j][1]) -
                    max(bottomLeft[i][1], bottomLeft[j][1]);

                maxLen = max(maxLen, min(min_width, min_height));
            }
        }

        return 1ll * maxLen * maxLen;
    }
};

