#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:

    void static cauculateArea(const vector<vector<int>>& squares, double mid,
                                double& subArea, double& topArea // output
                                )
    {
        for (auto& square : squares)
        {
            int ysub = square[1];
            int ytop = ysub+square[2];
            if (ysub >= mid)
                topArea += 1.0 * square[2] * square[2];
            else if (ytop <= mid)
                subArea += 1.0 * square[2] * square[2];
            else
            {
                subArea += (mid - ysub) * square[2];
                topArea += (ytop - mid) * square[2];
            }
        }
    }

    double separateSquares1(vector<vector<int>>& squares) {
        const double eps = 1e-5;
        // leetcode::print2DVector(squares);
        // cout<<"\n";

        vector<double> lines;
        lines.push_back(0.0);
        for (auto& square : squares)
        {
            double yupper = 1.0 * square[1] + square[2];
            lines.push_back(yupper);
        }
        sort(lines.begin(), lines.end());

        // discrete part
        int l = 0, r = lines.size() -1;
        int mid = (l+r)>>1;

        double subArea, topArea;

        while (r - l > 1)
        {
            subArea = 0.0;
            topArea = 0.0;

            cauculateArea(squares, lines[mid], subArea, topArea);
            // cout<<mid<<", "<<subArea<<", "<<topArea<<endl;

            if (fabs(topArea - subArea) < eps)
                return lines[mid];
            if (topArea > subArea)
                l = mid;
            else r = mid;

            mid = (l+r)>>1;
        }

        // continuous part
        double ll = lines[l];
        double rr = lines[r];
        double midline = (ll+rr)/2.0;

        while (rr-ll > eps)
        {
            subArea = 0.0;
            topArea = 0.0;

            cauculateArea(squares, midline, subArea, topArea);
            // cout<<midline<<", "<<subArea<<", "<<topArea<<endl;

            if (fabs(topArea - subArea) < eps)
                return midline;
            if (topArea > subArea)
                ll = midline;
            else rr = midline;

            midline = (ll+rr)/2.0;

        }

        return midline;
    }

    double separateSquares(vector<vector<int>>& squares) {
        const double eps = 1e-5;
        // leetcode::print2DVector(squares);
        // cout<<"\n";

        double ymax = 0;
        double totalArea = 0;
        for (auto& square : squares)
        {
            ymax = max(ymax, 1.0 * (square[1]+square[2]));
            totalArea += 1.0 * square[2] * square [2];
        }

        double l = 0;
        double r = ymax;
        double mid = (l+r)/2.0;

        auto check = [&](double _mid) -> bool
        {
            double subArea = 0.0;
            for (auto& square : squares)
            {
                if (square[1] < _mid)
                {
                    subArea += 1.0 * square[2] * min(square[2] * 1.0, _mid-square[1]);
                }
            }
            return subArea >= totalArea / 2.0;
        };

        while (r-l > eps)
        {
            if (check(mid))
                r = mid;
            else
                l = mid;
            mid = (l+r)/2.0f;
        }

        return r;
    }
};

