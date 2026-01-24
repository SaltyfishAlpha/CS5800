#include <vector>
using namespace std;

class Solution {
public:

    void merge(vector<int>& arr, vector<int>& tmp, int l, int r)
    {
        if (l == r) return;
        int mid = (l+r)>>1;

        merge(arr, tmp, l, mid);
        merge(arr, tmp,mid+1, r);

        int tpl = 0, tpr = 0, tpp = 0;
        while (l+tpl<=mid && mid+tpr+1<=r)
        {
            if (arr[l+tpl] <= arr[mid+tpr+1])
                tmp[tpp++] = arr[l+tpl++];
            else tmp[tpp++] = arr[mid+1+tpr++];
        }

        while (l+tpl<=mid)
            tmp[tpp++] = arr[l+tpl++];

        while (mid+tpr+1<=r)
            tmp[tpp++] = arr[mid+1+tpr++];

        copy(tmp.begin(), tmp.begin()+tpp, arr.begin()+l);
    }

    void insertSort(vector<int>& arr, int l, int r)
    {
        for (int i = l+1; i<=r; ++i)
        {
            int j = i-1;
        }
    }

    vector<int> mergeSort(vector<int>& arr) {
        vector<int> tmp(arr.size());
        merge(arr, tmp, 0, arr.size()-1);
        return arr;
    }
};

