#include <vector>
using namespace std;

class Solution {
public:
	// random pick pivot in [l, r]
	int get_pivot_rand(int l, int r) {
		return rand()%(r-l+1)+l;
	}

	int get_pivot_mid(int l, int r) {
		return (r-l>>1)+l;
	}

	int getPivot(int l, int r) {
		return get_pivot_mid(l, r);
	}

	// [l, r]
	int partition(vector<int>& nums, int index, int l, int r) {
		swap(nums[index], nums[r]);
		int i = l-1;
		for(int j = l; j < r; ++j) {
			if (nums[j] > nums[r]) {
				swap(nums[++i], nums[j]);
			}
		}
		swap(nums[i+1], nums[r]);
		return i+1;
	}

	int quick_select(vector<int>& nums, int k) {
		int l = 0, r = nums.size() - 1, p = getPivot(l, r);
		while (r-l > 1) {
			p = partition(nums, p, l, r);
			if (p == k) return nums[p];

			if (p > k) {
				r = p-1;
				p = getPivot(l, r);
			} else {
				l = p+1;
				p = getPivot(l, r);
			}
		}
		if (nums[l] < nums[r]) swap(nums[l], nums[r]);
		return nums[k];
	}

	int quick_select_3way(vector<int>& nums, int l, int r, int k) {
		if (l == r) return nums[l];

		int pivot = nums[getPivot(l, r)];
		int ll = l, i = l, rr = r;

		while(i <= rr) {
			if (nums[i] > pivot) {
				swap(nums[ll++], nums[i++]);
			} else if (nums[i] < pivot) {
				swap(nums[rr--], nums[i]);
			} else {
				i++;
			}
		}

		if (ll <= k && k <= rr)
			return nums[k];
		if (k < ll)
			return quick_select_3way(nums, l, ll-1, k);
		return quick_select_3way(nums, rr+1, r, k);
	}


	int findKthLargest(vector<int>& nums, int k) {
		srand(0);
		// return quick_select(nums, k-1);
		return quick_select_3way(nums, 0, nums.size()-1, k-1);
	}
};