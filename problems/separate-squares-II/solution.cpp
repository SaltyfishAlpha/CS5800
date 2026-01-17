#include <algorithm>
#include <set>
#include <vector>
using namespace std;

static const int IN = 1;
static const int OUT = -1;

struct SegmentTree
{
    vector<int> width;
    vector<int> count;
    vector<int> xs;
    int lens;

    explicit SegmentTree(const vector<int>& xs)
    {
        this->xs = xs;
        lens = xs.size() - 1;

        width.resize(4 * lens, 0.0);
        count.resize(4 * lens, 0);

    }

    // edge = { l, r, height, type }
    void update(int l, int r, int type)
    {
        push_down(0, 0, lens-1, l, r, type);
    }

    // l, r: index of ycoord
    int query()
    {
        return width[0]; // root node
    }

    void push_down(int index, int l, int r, int ll, int rr, int type)
    {
        if (rr <= xs[l] || xs[r+1] <= ll)
            return; // out of range
        if (ll <= xs[l] && xs[r+1] <= rr)
            count[index] += type;
        else
        {
            int mid = (l + r)>>1;
            push_down((index<<1)+1, l, mid, ll, rr, type);
            push_down((index<<1)+2, mid+1, r, ll, rr, type);
        }

        if (count[index] > 0)
        {
            width[index] = xs[r + 1]-xs[l];
        } else
        {
            if (l == r)
                width[index] = 0;
            else
            {
                width[index] = width[(index<<1) + 1] + width[(index<<1) +2];
            }
        }
    }
};

class Solution {
public:

    double separateSquares(vector<vector<int>>& squares) {

        vector<tuple<int, int, int, int>> edges; // y, l, r, type
        set<int> xs;

        for (auto& square : squares)
        {
            int xl = square[0];
            int yl = square[1];
            int xr = square[0] + square[2];
            int yr = square[1] + square[2];
            edges.emplace_back(yl, xl, xr, IN);
            edges.emplace_back(yr, xl, xr, OUT);
            xs.insert(xl);
            xs.insert(xr);
        }

        sort(edges.begin(), edges.end());

        SegmentTree tree(vector<int>(xs.begin(), xs.end()));

        vector<double> sums;
        vector<int> widths;
        double total = 0.0;
        int prev = get<0>(edges[0]);

        for (auto& [y, xl, xr, type] : edges)
        {
            int delta_y = y - prev;
            int width = tree.query();
            total += 1LL * delta_y * width;
            sums.push_back(total);

            tree.update(xl, xr, type);

            widths.push_back(tree.query());

            prev = y;
        }
        //
        // return 0.0f;

        double target = total/2;
        int i = lower_bound(sums.begin(), sums.end(), target) - sums.begin() -1;

        return (total - 2 * sums[i]) / (widths[i] * 2.0) + get<0>(edges[i]);
    }
};

