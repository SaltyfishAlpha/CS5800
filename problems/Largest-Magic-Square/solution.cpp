#include <vector>
using namespace std;

class Solution {
public:
    int largestMagicSquare(vector<vector<int>>& grid) {
        // leetcode::print2DVector(grid); cout<<"\n-----------\n";

        int w = grid[0].size();
        int h = grid.size();
        int n = min(w, h);

        vector<vector<int>> rowSum;
        vector<vector<int>> colSum;
        vector<vector<int>> r_diaSum;
        vector<vector<int>> l_diaSum;

        rowSum.resize(h+2, {});
        colSum.resize(h+2, {});
        r_diaSum.resize(h+2, {});
        l_diaSum.resize(h+2, {});

        for (int i = 0; i < h+2; ++i)
        {
            rowSum[i].resize(w+1, 0);
            colSum[i].resize(w+1, 0);
            r_diaSum[i].resize(w+1, 0);
            l_diaSum[i].resize(w+1, 0);
        }

        for (int i = 1; i <= h; ++i)
            for (int j = 1; j <= w; ++j)
            {
                rowSum[i][j] = grid[i-1][j-1] + rowSum[i][j-1];
                colSum[i][j] = grid[i-1][j-1] + colSum[i-1][j];
                r_diaSum[i][j] = grid[i-1][j-1] + r_diaSum[i-1][j-1];
                l_diaSum[h-i+1][j] = grid[h-i][j-1] + l_diaSum[h-i+2][j-1];
            }

        // leetcode::print2DVector(colSum); cout<<endl;
        // leetcode::print2DVector(rowSum); cout<<endl;
        // leetcode::print2DVector(r_diaSum); cout<<endl;
        // leetcode::print2DVector(l_diaSum); cout<<endl;

        while (n>1)
        {
            for (int i = 1; i <= h - n + 1; ++i)
            {
                for (int j = 1; j <= w - n + 1; ++j)
                {
                    int sum_r_diag = r_diaSum[i+n-1][j+n-1] - r_diaSum[i-1][j-1];
                    int sum_l_diag = l_diaSum[i][j+n-1] - l_diaSum[i+n][j-1];
                    if (sum_l_diag != sum_r_diag) continue;
                    bool flag = true;
                    for (int k = 0; k < n; ++k)
                    {
                        int sum_col = colSum[i+n-1][j+k] - colSum[i-1][j+k];
                        int sum_row = rowSum[i+k][j+n-1] - rowSum[i+k][j-1];
                        if (sum_col != sum_r_diag || sum_row != sum_r_diag)
                        {
                            flag = false;
                            break;
                        }
                    }
                    if (flag)
                        return n;
                }
            }
            n--;
        }

        return 1;
    }
};

