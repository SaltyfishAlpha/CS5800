#include <algorithm>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
public:
    int maximizeSquareArea(int m, int n, vector<int>& hFences, vector<int>& vFences) {
        // cout<<m<<"\n"<<n<<"\n"<<hFences.size()<<"\n"<<vFences.size()<<"\n";
        hFences.push_back(1);
        hFences.push_back(m);
        vFences.push_back(1);
        vFences.push_back(n);
        sort(hFences.begin(), hFences.end());
        sort(vFences.begin(), vFences.end());
        // leetcode::printVector(hFences); cout<<"\n";
        // leetcode::printVector(vFences); cout<<"\n";

        unordered_set<int> hSum;
        unordered_set<int> vSum;

        for (int i = 0; i < hFences.size(); ++i)
        {
            for (int j = i+1; j < hFences.size(); ++j)
                hSum.insert(hFences[j] - hFences[i]);
        }

        for (int i = 0; i < vFences.size(); ++i)
        {
            for (int j = i+1; j < vFences.size(); ++j)
                vSum.insert(vFences[j] - vFences[i]);
        }

        // cout<<hSum.size()<<"\n"<<vSum.size()<<"\n";
        // leetcode::printVector(vector<int>(hSum.begin(), hSum.end())); cout<<"\n";
        // leetcode::printVector(vector<int>(vSum.begin(), vSum.end())); cout<<"\n";

        int maxLen = 0;
        for (int h : hSum)
        {
            if (vSum.find(h) != vSum.end()) maxLen = max(maxLen, h);
        }

        if (maxLen == 0) return -1;
        return 1ll * maxLen * maxLen % 1000000007;
    }
};

